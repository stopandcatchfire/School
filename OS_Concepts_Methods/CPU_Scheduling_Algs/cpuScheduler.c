//Nick Wantz
//Assignment 3 CPU Scheduling
//Prof. Shobaki
//CSc 139-03

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

void roundRobin(int p,int tq, int totalTime);
void shortestJobFirst(int p, int totalTime);
void prnoP(int p, int totalTime);
void prwithP(int p, int totalTime);

FILE *outputFile = NULL;
char rr[80];
char sjf[80];
char prnp[80];
char prp[80];
char processDone[1000];
int arrivalTime[1000];
int cpuBurst[1000];
int priority[1000];


void init(){
	strcpy(sjf,"SJF\n");
	strcpy(prnp,"PR_noPREMP\n");
	strcpy(prp,"PR_withPREMP\n");
}

int main(int argc, char*  argv[]){

	FILE *inputFile = NULL;
	int procs = 0;
	char input[256];
	char alg[80];
	int timeQuant = 0;
	char temp = 0;
	int i = 0;
	char *token;
	int totalTime = 0;


	inputFile = fopen("input.txt","r");
	outputFile = fopen("output.txt","w");
	
	//check input/output file was found
	if(!inputFile)	
		return 1;

	if(!outputFile)
		return 1;

	//initialize cmp strings may need to use for future initializations
	init();			

	fgets(alg, sizeof alg, inputFile);		//Pulls first line to determine Algorithm to use
	fgets(input, sizeof input, inputFile);		//Pulls second line to determine number of processis
	
	fprintf(outputFile, "%s", alg);			//Prints algorithm used to output.txt

	//atoi second line, for process number
	procs = atoi(&input[0]);
		
	//for each process read in it's variables: P#,Arrival Time, CPUBurst, Priority
	for(i; i<procs; i++){
		int j = 0;
		fgets(input, sizeof input, inputFile);
		token = strtok(input," ");	//pull first token out of line, space delimiter
		processDone[i] = false;
		while(token != NULL){
			if(j==1){
				arrivalTime[i] = atoi(token);
			}
			else if(j==2){
				cpuBurst[i] = atoi(token);
			}
			else if(j==3){
				priority[i] = atoi(token);
			}
			j++;
			token = strtok(NULL," ");
		}
				
		totalTime += cpuBurst[i];				
	}

	//Determines what algorithm to use and proceeds to call function	
	if(0==strcmp(alg,sjf)){
		shortestJobFirst(procs,totalTime);
	}
	else if (0==strcmp(alg,prnp)){
		prnoP(procs,totalTime);
	}
	else if(0==strcmp(alg,prp)){
		prwithP(procs,totalTime);
	}
	else{
		temp = alg[3];
		timeQuant = atoi(&alg[3]);
		roundRobin(procs, timeQuant, totalTime);
	}


	fclose(inputFile);
	fclose(outputFile);

	return(0);
}

void roundRobin(int p, int tq, int totalTime){
	int i,j = 0;
	int temp = 0;
	int order[p];
	int atTemp[p];
	int timeElapsed = 0;
	int burst = 0;
	int wt[p];
	int totalWt;
	int burstTime[p];
	float avgWt;
	
	//copy arrivalTime since it needs to be moved around for sort
	for(i=0;i<p;i++){
		order[i] = i;
		atTemp[i] = arrivalTime[i];
		burstTime[i] = cpuBurst[i];	//need this to calculate avg time since decrementing global value
	}
	//sort by arrival time
	for(i=0;i<p;i++){
		for(j=i+1; j<p; j++){
			if(atTemp[i]>atTemp[j]){
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
				temp = atTemp[i];
				atTemp[i] = atTemp[j];
				atTemp[j] = temp;
			}
		}
	}
	i,j,temp = 0;
	//total time is all bursts combined.  timeElapsed is a running total of time gone by.
	while(totalTime>0){
		if(i<p){
			temp = order[i];
			if(arrivalTime[temp]<=timeElapsed && processDone[temp]!=true){
				burst = cpuBurst[temp] - tq;
				fprintf(outputFile, "%d %d\n", timeElapsed, temp+1);
				if(burst<=0){
					processDone[temp] = true;						
					timeElapsed += cpuBurst[temp];
					totalTime -= cpuBurst[temp];
					wt[temp] = timeElapsed - (arrivalTime[temp] + burstTime[temp]);
				}
				else{
					timeElapsed += tq;
					totalTime -= tq;
					cpuBurst[temp] -= tq;
				}
			}			
		i++;
		}
		else{
			i=0;
		}	
	}
	for(i=0;i<p;i++){
		avgWt += wt[i];
	}
	avgWt = avgWt/p;	
	fprintf(outputFile, "AVG Waiting Time: %f\n", avgWt);
}

void shortestJobFirst(int p, int totalTime){
	int burstOrder[p];
	int i,j=0;
	int burst[p];
	int arrival[p];
	int temp = 0;
	int elapsedTime = 0;
	int timeChangeFlg = 0;
	float totalWait = 0;
	float avgWt = 0;
	
	for(i=0;i<p;i++){
		burstOrder[i]=i;
		burst[i] = cpuBurst[i];
		arrival[i] = arrivalTime[i];
	}
	//sorted by burst length
	for(i=0;i<p;i++){
		for(j=i+1; j<p; j++){
			//if burst times are equal however, arrival time is taken into account.  Time variable checked after sort.
			if(burst[i]>burst[j] || (burst[i] == burst[j] && arrivalTime[burstOrder[i]] > arrivalTime[burstOrder[j]])){
				temp = burst[i];
				burst[i] = burst[j];
				burst[j] = temp;
				temp = burstOrder[i];
				burstOrder[i] = burstOrder[j];
				burstOrder[j] = temp;
			}
		}
	}
	
	//since no preemption, time increased when a process gets cpu. If no process gets cpu, time is increased by 1.  
	while(totalTime > 0){
		for(i=0;i<p;i++){
			temp = burstOrder[i];
			if(arrivalTime[temp] <= elapsedTime && processDone[temp] == false){	
				totalWait += (elapsedTime-arrivalTime[temp]);
				fprintf(outputFile, "%d %d\n", elapsedTime, temp+1);
				elapsedTime += cpuBurst[temp];
				totalTime -= cpuBurst[temp];
				timeChangeFlg = true;
				processDone[temp] = true;
				break;
			}
		}
		if(timeChangeFlg == false){
			elapsedTime += 1;
			totalTime -= 1;
		}
		else{			
			timeChangeFlg == false;
		}			
	}
	
	avgWt = totalWait/p;

	fprintf(outputFile, "AVG Waiting Time: %f\n", avgWt);
}

//priority without preemption
void prnoP(int p, int totalTime){
	int order[p];
	int i,j = 0;
	int pri[p];
	int temp = 0;
	int elapsedTime = 0;
	int timeChangeFlg = 0;
	float totalWait = 0;
	float avgWt = 0;
	
	for(i=0;i<p;i++){
		order[i] = i;
		pri[i] = priority[i];
	}
	//sorted by priority
	for(i=0;i<p;i++){
		for(j=i+1; j<p; j++){
			if(pri[i] > pri[j] || (pri[i] == pri[j] && arrivalTime[order[i]] > arrivalTime[order[j]])){
				temp = pri[i];
				pri[i] = pri[j];
				pri[j] = temp;
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}
	}
	while(totalTime > 0){
		for(i=0;i<p;i++){
			temp = order[i];
			if(elapsedTime >= arrivalTime[temp] && processDone[temp] == false){
				totalWait += elapsedTime - arrivalTime[temp];
				fprintf(outputFile, "%d %d\n", elapsedTime, temp+1);
				processDone[temp] = true;
				elapsedTime += cpuBurst[temp];
				totalTime -= cpuBurst[temp];
				timeChangeFlg = true;
			}
		}
		
		if(timeChangeFlg == false){
			elapsedTime += 1;
			totalTime -= 1;
		}
		else{
			timeChangeFlg = false;
		}
	}
	avgWt = totalWait/p;
	fprintf(outputFile, "AVG Waiting Time: %f\n", avgWt);
}

//priority with preemption
void prwithP(int p, int totalTime){
	int order[p];
	int i,j = 0;
	int pri[p];
	int temp = 0;
	int elapsedTime = 0;
	int timeChangeFlg = 0;
	int ctxSwitchFlg = -1;
	int burstTime[p];
	float wt[p];
	float avgWt = 0;
	
	for(i=0;i<p;i++){
		order[i] = i;
		pri[i] = priority[i];
		burstTime[i] = cpuBurst[i];	//stored since decrementing cpuBurst
	}
	//sorted by priority
	for(i=0;i<p;i++){
		for(j=i+1;j<p;j++){
			if(pri[i] > pri[j]){
				temp = pri[i];
				pri[i] = pri[j];
				pri[j] = temp;
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
			}
		}
	}

	while(totalTime > 0){
		for(i=0;i<p;i++){
			temp = order[i];
			if(elapsedTime >= arrivalTime[temp] && processDone[temp] == false){
				if(ctxSwitchFlg != temp){
					fprintf(outputFile, "%d %d\n", elapsedTime, temp+1);
					ctxSwitchFlg = temp;
				}
				elapsedTime += 1;
				totalTime -= 1;
				cpuBurst[temp] -= 1;
				
				if(cpuBurst[temp] == 0){
					processDone[temp] = true;
					wt[temp] = elapsedTime - (arrivalTime[temp] + burstTime[temp]);
				}
				
				break;
			}	
		}
	}
	for(i=0;i<p;i++){
		avgWt += wt[i];
	}
	avgWt /= p;

	fprintf(outputFile, "AVG Waiting Time: %f\n", avgWt);
}
