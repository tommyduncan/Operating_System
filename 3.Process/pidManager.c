#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define MIN_PID 300
#define MAX_PID 5000

typedef struct Process_Strcture{
		int id;
		bool idle;
}process;

process *pid = NULL;

int allocate_map(void);
int allocate_pid(void);
void release_pid(int processId);

int main(){
		int i = 0;
		if(allocate_map()){
				printf("Data structure of pid initialize successfully.\n");

				for(i = 0; i < 10; i++){
						if(allocate_pid() >= 0){
								printf("Process %d: pid = %d\n", i, pid[i].id);
						}
				}

				release_pid(302);
				printf("Process which pid is 302 has been release.\n");

				release_pid(308);
				printf("Process which pid is 308 has been release.\n");

				printf("Process %d: pid = %d\n", i++, pid[allocate_pid()]);
				printf("Process %d: pid = %d\n", i++, pid[allocate_pid()]);
				printf("Process %d: pid = %d\n", i++, pid[allocate_pid()]);
		}
		return 0;
}

int allocate_map(void){
		int i = 0;
		pid = (process *)malloc(sizeof(process) * (MAX_PID - MIN_PID + 1));
		if(pid){
				for(i = 0; i < (MAX_PID - MIN_PID + 1); i++){
						pid[i].idle = true;
				}
				return 1;
		}
		return -1;
}

int allocate_pid(void){
		int i = 0;
		for(i = 0; i < MAX_PID - MIN_PID + 1; i++){
				if(pid[i].idle){
						pid[i].id = i + MIN_PID;
						pid[i].idle = false;

						return i;
				}
		}
		return -1;
}

void release_pid(int processId){
		pid[processId - MIN_PID].id = 0;
		pid[processId - MIN_PID].idle = true;
}
