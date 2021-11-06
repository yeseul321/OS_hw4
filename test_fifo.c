#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <termio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

#define SMALL 1000
#define MID 2000
#define LARGE 3000

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
	int tem;
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

	//setpriority(PRIO_PROCESS, 90, getpid());

	for(int i=0;i<21;i++){
		pid[i] = fork();
		if(pid[i]>0){
			//printf("***process %d begins***\n", pid[i]);
			//sprintf(msg2, "chrt -p %d", pid[i]);
			//system(msg2);
		}
		else if(pid[i] == 0){
			//sprintf(msg2, "chrt -p %d", getpid());
			//if(tem = getpriority(PRIO_PROCESS, getpid())<0){
			//	printf("error\n");
			//}
			//else
			//	printf("%d : %d\n", getpid(), tem);

			if(i>=0&&i<7){
				//small nice
				//nice(19);
				//system(msg2);
				printf("***process %d begins***\n", getpid());
				bubble(numArr_large, LARGE);
				printf("+++process %d ends+++\n", getpid());
				num = 0;
			}
			else if(i>=7&&i<14){
				//mid nice
				//system(msg2);
				printf("***process %d begins***\n", getpid());
				bubble(numArr, MID);
				printf("+++process %d ends+++\n", getpid());
				num = 1;
			}
			else{
				//large nice
				//nice(-20);
				//system(msg2);
				printf("***process %d begins***\n", getpid());
				bubble(numArr_small, SMALL);
				printf("+++process %d ends+++\n", getpid());
				num = 2;
			}
			//printf("+++process %d ends+++(%d)\n", getpid(), num);
			exit(0);
		}
	}
	//system("top");
	while((endpid=wait(&state))>0){
		//printf("+++process %d ends+++\n", endpid);
	}
	free(numArr);
	free(numArr_large);
	free(numArr_small);
	return 0;
}

