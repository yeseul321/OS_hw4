#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	pid_t pid[21]; 
	pid_t endpid;
	char msg2[50];
	int state;
	int temp = 0;
	srand(time(NULL));

	int *numArr = (int*)malloc(sizeof(int)*10000);
	for(int i=0;i<10000;i++){
		numArr[i] = rand()%1000;
	}
	
	for(int i=0;i<21;i++){
		pid[i] = fork();
		if(pid[i]>0){
			printf("***process %d begins***\n", pid[i]);
			//sprintf(msg2, "chrt -p %d", pid[i]);
			//system(msg2);
		}
		else if(pid[i] == 0){
			for(int j = 0;j < 10000; j++){
				for(int k = 0;k < 10000; k++){
					if(numArr[k]>numArr[k+1]){
						temp = numArr[k];
						numArr[k] = numArr[k+1];
						numArr[k+1] = temp;
					}
				}
			}
			printf("+++process %d ends+++\n", getpid());
			exit(0);
		}
	}
	while((endpid=wait(&state))>0){
		//printf("+++process %d ends+++\n", endpid);
	}
	free(numArr);
	return 0;
}

