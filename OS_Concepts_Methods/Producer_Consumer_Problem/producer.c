/*
CSC139 
Spring 2017
First Assignment
Wantz, Nick
Section #3
OSs Tested on: Linux, Mac, etc.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>


// Size of shared memory block
// Pass this to ftruncate and mmap
#define SHM_SIZE 8192
 
// Global pointer to the shared memory block
// This should receive the return value of mmap
// Don't change this pointer in any function
void* gShmPtr;
 
// You won't necessarily need all the functions below
void Producer(int, int, int);
void InitShm(int, int);
void SetBufSize(int);
void SetItemCnt(int);
void SetIn(int);
void SetOut(int);
void SetHeaderVal(int, int);
int GetBufSize();
int GetItemCnt();
int GetIn();
int GetOut();
int GetHeaderVal(int);
void WriteAtBufIndex(int, int);
int ReadAtBufIndex(int);
int GetRand(int, int);
  
int main(int argc, char* argv[]){

	pid_t pid;
	int bufSize;
	int itemCnt;
	int randSeed;

	if(argc != 4){
		printf("Invalid number of command-line arguments\n");
		exit(1);
	}

	bufSize = atoi(argv[1]);
	itemCnt = atoi(argv[2]);
	randSeed = atoi(argv[3]);

	InitShm(bufSize, itemCnt);
	
		pid = fork();

		if(pid<0){
			fprintf(stderr, "Fork Failed\n");
			exit(1);
		}
		else if(pid==0){
			printf("Launching Consumer\n");
			execlp("./consumer","consumer",NULL);
		}
		else{
			printf("Starting Producer\n");
			
			Producer(bufSize, itemCnt, randSeed);
		
			printf("Producer done and waiting for consumer\n");
			wait(NULL);		
			printf("Consumer Completed\n");
		}

	return 0;

}

void InitShm(int bufSize, int itemCnt){

	int shm_fd;
	int in = 0;
	int out = 0;
	const char *name = "OS_HW1_nickwantz";

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SHM_SIZE);
	gShmPtr = mmap(0,SHM_SIZE,PROT_READ | PROT_WRITE,MAP_SHARED,shm_fd,0);


	SetBufSize(bufSize);
	SetItemCnt(itemCnt);
	SetIn(in);
	SetOut(out);
}


void Producer(int bufSize, int itemCnt, int randSeed){

	int in = 0;
	int out = 0;
	int i = 0;
	int val;

	srand(randSeed);

	while(itemCnt>0){
		
		val = GetRand(0,1000);
		
		while(((GetIn()+1)%bufSize)==GetOut());

		i++;
		WriteAtBufIndex(in,val);
		printf("Producing Item %d with value %d at Index %d\n",i,val,GetIn());
		in = (GetIn()+1)%bufSize;
		SetIn(in);
		itemCnt--;
	}		
	

	printf("Producer Complete\n");
}	





void SetBufSize(int val){
        SetHeaderVal(0,val);
}

void SetItemCnt(int val){
	SetHeaderVal(1,val);
}

void SetIn(int val){
	SetHeaderVal(2,val);
}

void SetOut(int val){
	SetHeaderVal(3,val);
}

void SetHeaderVal(int i, int val){
	void* ptr = gShmPtr + i*sizeof(int);
	memcpy(ptr, &val, sizeof(int));
}

int GetItemCnt(){
	return GetHeaderVal(1);
}

int GetIn(){
	return GetHeaderVal(2);
}

int GetOut(){
	return GetHeaderVal(3);
}

int GetHeaderVal(int i){
	int val;
	void* ptr = gShmPtr + i*sizeof(int);
	memcpy(&val, ptr, sizeof(int));
	return val;
}

void WriteAtBufIndex(int indx, int val){
	void* ptr = gShmPtr + 4*sizeof(int) + indx*sizeof(int);
	memcpy(ptr, &val, sizeof(int));
}

int GetRand(int x, int y){
	int r = rand();
	r = x + r%(y-x+1);
	return r;
}




