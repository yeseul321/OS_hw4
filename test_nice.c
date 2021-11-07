#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SMALL 5000
#define MID 10000
#define LARGE 15000

void bubble(int arr[], int count){
	int temp = 0;
	for(int j = 0;j < count; j++){
		for(int k = 0;k < count; k++){
			if(arr[k]>arr[k+1]){
				temp = arr[k];
				arr[k] = arr[k+1];
				arr[k+1] = temp;
			}
		}
	}
}


int main(void){
	pid_t pid[21]; 
	pid_t endpid;
	char msg2[50];
	int state;
	int num;
	srand(time(NULL));

	int *numArr = (int*)malloc(sizeof(int)*MID);
	int *numArr_small = (int*)malloc(sizeof(int)*SMALL);
	int *numArr_large = (int*)malloc(sizeof(int)*LARGE);

	for(int i=0;i<LARGE;i++){
		numArr_large[i] = rand()%1000;
	}
	for(int i = 0;i<SMALL;i++){
		numArr_small[i] = rand()%1000;
	}
	for(int i = 0;i<MID;i++){
		numArr[i] = rand()%1000;
	}
	
	for(int i=0;i<21;i++){
		pid[i] = fork();
		if(pid[i]>0){
			printf("***process %d begins***\n", pid[i]);
		}
		else if(pid[i] == 0){
			sprintf(msg2, "chrt -p %d", getpid());
			if(i>=0&&i<7){
				//high nice, small array
				nice(19);
				bubble(numArr_small, SMALL);
				num = 0;
			}
			else if(i>=7&&i<14){
				//mid nice, mid array
				bubble(numArr, MID);
				num = 1;
			}
			else{
				//low nice, large array
				nice(-20);
				bubble(numArr_large, LARGE);
				num = 2;
			}
			printf("+++process %d ends+++(%d)\n", getpid(), num);
			exit(0);
		}
	}
	while((endpid=wait(&state))>0){
		//printf("+++process %d ends+++\n", endpid);
	}
	printf("----------------All processes are finished!!!----------------\n");

	free(numArr);
	free(numArr_large);
	free(numArr_small);
	return 0;
}

