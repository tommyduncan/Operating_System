#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define BUFFER_SIZE 128

int main( int argc, char* argv[] ) {
		int filePipe[2];
		pid_t pid;

		char readBuffer[BUFFER_SIZE];

		pipe(filePipe);

		if( argc < 3 || argc > 3) {
				printf("ERROR: Need exactly 2 parameters.\n");
				exit(1);
		}

		int sourceFile = open(argv[1], 0);
		int targetFile = open(argv[2], O_RDWR|O_CREAT|O_APPEND, 0666);

		if(sourceFile < -1){
				printf("ERROR: Failed to open source file.\n");
				exit(1);
		}

		if(targetFile < -1){
				printf("ERROR: Failed to open target file.\n");
				exit(1);
		}


		pid = fork();

		if (pid == 0) {    /* ========== Child process ========== */
				close(filePipe[1]);

				/* Read from the parent process, then write text into target file. */
				while (read(filePipe[0], readBuffer, sizeof(readBuffer)) > 0) {
						write(targetFile, readBuffer, strlen(readBuffer) - 1);
						memset(readBuffer, 0, BUFFER_SIZE);
				}

				close(filePipe[0]);
				close(targetFile);
		}else{    /* ========== Parent process ========== */
				close(filePipe[0]);

				/* Read text from source file, then write into child process. */
				while (read(sourceFile, readBuffer, sizeof(readBuffer)) > 0) {
						write(filePipe[1], readBuffer, sizeof(readBuffer));
						memset(readBuffer, 0, BUFFER_SIZE);
				}

				close(filePipe[1]);
				close(sourceFile);
				wait(NULL);
		}
}
