//Nick Wantz
//Assignment 4 Memory Managment
//Prof. Shobaki
//CSc 139-03


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

void fifo();
void optimal();
void lru();

FILE *outputFile = NULL;
FILE * inputFile = NULL;
int requestOrder[10000];
int pages = 0;
int frames = 0;
int pgRequests = 0;


int main(int argc, char* argv[])
{
	int j = 0;
	char input[256];
	char *token;

	inputFile = fopen("input.txt","r");
	outputFile = fopen("output.txt","w");

	if(!inputFile)
		return 1;

	if(!outputFile)
		return 1;

	fgets(input, sizeof input, inputFile);
	token = strtok(input," ");
	while(token != NULL){
		if(j==0){
			pages = atoi(token);
		}
		else if(j==1){
			frames = atoi(token);
		}
		else if(j==2){
			pgRequests = atoi(token);
		}
		j++;
		token = strtok(NULL," ");
	}
	//debug
	//printf("Pages: %d, Frames: %d, PageRequests: %d\n", pages, frames, pgRequests);
	
	for(j=0; j<pgRequests; j++){
		
		fgets(input, sizeof input, inputFile);
		requestOrder[j] = atoi(input);
		//debug
		printf("%d\n", requestOrder[j]);
	}




	fifo();
	optimal();
	lru();

	fclose(inputFile);
	fclose(outputFile);

	return 0;
}

void fifo()
{
	int i = 0;
	int j = 0;
	int fi = 0;
	int fFrames = frames;
	int pageTable[frames];
	int pgLoaded = false;
	int request = 0;
	int replaceOrder[pgRequests-frames];   //allows enough size for worst case when every request after frames are filled result in a replacement
	int replaceOrderIndex = 0;
	int faults = 0;

	for(j=0;j<frames;j++){
		pageTable[j] = -1;
	}

	while(i<pgRequests){
		request = requestOrder[i];
		for(j=0;j<frames;j++){
			if(request == pageTable[j]){
				printf("Page %d already in Frame %d\n", request, j);
				pgLoaded = true;
				break;
			}	
		}

		if(pgLoaded == false && fFrames>0){
			for(j=0;j<frames;j++){
				if(pageTable[j] == -1){
					printf("Page %d loaded into Frame %d\n", request, j);
					pageTable[j] = request;
					replaceOrder[replaceOrderIndex] = request;
					replaceOrderIndex++;
					faults++;
					fFrames--;
					break;
				}
			}
		}
		else if(pgLoaded == false){
			int replace = replaceOrder[fi];
			for(j=0;j<frames;j++){
				if(replace == pageTable[j]){
					printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", pageTable[j], j, request, j);
					pageTable[j] = request;
					replaceOrder[replaceOrderIndex] = request;
					replaceOrderIndex++;
					fi++;
					faults++;
				}
			}
		}
		pgLoaded = false;
		i++;						
	}
	printf("%d page faults\n", faults);	
}

void optimal()
{

	int i = 0;
	int j = 0;
	int k = 0;
	int fFrames = frames;
	int pageTable[frames];
	int request = 0;
	int faults = 0;
	int nextUse[frames];	
	int nextUseIndex = 0;
	int pgLoaded = false;
	int count = 0;
	int brkFlg = false;
	int longestUnused = 0;
	int replaceIndex = 0;


	for(j=0;j<frames;j++){
		pageTable[j] = -1;
	}

	//cycle for every page request
	while(i<pgRequests){
		request = requestOrder[i];
		
		//if request is already in frame you're done with iteration
	 	for(j=0;j<frames;j++){
			if(request == pageTable[j]){
				printf("Page %d already in Frame %d\n", request, j);
				pageTable[j] = request;
				pgLoaded = true;
				break;
			}
		}

		//if request not in frame, but there are free frames
		if(pgLoaded == false && fFrames>0){
			for(j=0;j<frames;j++){
				if(pageTable[j] == -1){
					printf("Page %d loaded into Frame %d\n", request, j);
					pageTable[j] = request;
					faults++;
					fFrames--;
					break;
				}
			}
		}
		//no free frames, request not in frame
		else if(pgLoaded == false){
			
			//sets next use, looking into future to find furthest out next use.  If unused in future request set to infinity = -1
			for(k=0;k<frames;k++){
				count = 0;
				for(j=i;j<pgRequests;j++){
					count++;
					if(requestOrder[j] == pageTable[k]){
						nextUse[k] = count;
						brkFlg = true;
						break;
					}	
				}
				if(brkFlg == false){
					nextUse[k] = -1;
				}
				brkFlg = false;					
			}

			//if frame is not used again unload and replace, else determine index of furthest out next use
			for(j=0;j<frames;j++){
				if(nextUse[j] == -1){
					printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", pageTable[j], j, request, j);
					pageTable[j] = request;
					brkFlg = true;
					faults++;
					break;
				}
				if(nextUse[j] > longestUnused){
					longestUnused = nextUse[j];
					replaceIndex = j;
				}
			}
			if(brkFlg == false){
				printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", pageTable[replaceIndex], replaceIndex, request, replaceIndex);
				pageTable[replaceIndex] = request;
				faults++;
			}		
			brkFlg = false;
		}
		i++;
		pgLoaded = false;
	}
	printf("%d page faults\n",faults);	
}

void lru()
{

	int i,j,k = 0;
	int lastUse[frames];
	int fFrames = frames;
	int pageTable[frames];
	int request = 0;
	int faults = 0;
	int pgLoaded = false;
	int lastUsed = 0;
	int lastUsedIndex = 0;

	for(j=0;j<frames;j++){
		pageTable[j] = -1;	
	}	

	//cycle for every page request
	while(i<pgRequests){
		request = requestOrder[i];
		
		//if request is already in frame you're done with iteration
	 	for(j=0;j<frames;j++){
			if(request == pageTable[j]){
				printf("Page %d already in Frame %d\n", request, j);
				pageTable[j] = request;
				pgLoaded = true;
				lastUse[j] = 0;
				break;
			}
		}

		//if request not in frame, but there are free frames
		if(pgLoaded == false && fFrames>0){
			for(j=0;j<frames;j++){
				if(pageTable[j] == -1){
					printf("Page %d loaded into Frame %d\n", request, j);
					pageTable[j] = request;
					faults++;
					fFrames--;
					lastUse[j] = 0;
					break;
				}
			}
		}
		//no free frames, request not in frame
		else if(pgLoaded == false){
			
			for(j=0;j<frames;j++){
				if(lastUse[j] > lastUsed){
					lastUsed = lastUse[j];
					lastUsedIndex = j;
				}	
			}

			printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n",pageTable[lastUsedIndex], lastUsedIndex, request, lastUsedIndex);
			pageTable[lastUsedIndex] = request;	
			lastUse[lastUsedIndex] = 0;
			faults++;
			lastUsed = lastUsedIndex = 0;

		}
		pgLoaded = false;
		i++;
		for(j=0;j<frames;j++){
			lastUse[j] += 1;
		}
	}
	printf("%d page faults\n",faults);
}
