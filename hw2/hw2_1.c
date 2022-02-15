#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CMD 2048
#define MAX_ARG 256

void ParseCommand(char *command, int *argc, char *argv[]);

int main(){
	char command[MAX_CMD];
	command[0] = command[MAX_CMD-1] = 0; // for safety
	int argc = 0;
	char *argv[MAX_ARG] = { NULL };
	char temp[1024];
	while (1){
		printf("$ ");
		fgets(command, MAX_CMD - 1, stdin);
		command[strlen(command) - 1] = 0; // trim \r
		if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
			break;
		ParseCommand(command, &argc, argv);

		
		if (strcmp(argv[0], "ls") == 0){
			system("ls");
		}else if(strcmp(argv[0],"mkdir")==0){
			mkdir(argv[1], 0755);			
		}else if(strcmp(argv[0],"rmdir")==0){
			rmdir(argv[1]);
		}else if(strcmp(argv[0],"cd")==0){
			chdir(argv[1]);
		}else if(strcmp(argv[0],"curdir")==0){
			getcwd(temp,1024);
			printf("current directory = %s\n",temp);
		}
	}
	printf("Bye!\n");
	return 0;
}

void ParseCommand(char *command, int *argc, char *argv[]){
	char *p = strtok(command," ");
	int i=0;
	while(p!=NULL){
		argv[i] = p;
		i++;
		p = strtok(NULL," ");
	}
	*argc = i;
}

