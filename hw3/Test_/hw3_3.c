#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_CMD 2048
#define MAX_ARG 256
#define BUFFER_SIZE 4096

void ParseCommand(char *command, int *argc, char *argv[]);
int ReadTextLine(int fd, char str[], int max_len);

// global variables
char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int main(int argc, char *argv[]){
	char line[300];
	char *arg[MAX_ARG] = { NULL };
	pid_t pid;
	int f;
	int count;
	if(argc<2){
		printf("Usage: %s <command_file>",arg[0]);
		return 0;
	}
	printf("%s\n", argv[1]);	
	f = open(argv[1],O_RDONLY);	

	while(ReadTextLine(f,line,BUFFER_SIZE)!=EOF){
		printf("command = [%s]\n",line);
 		ParseCommand(line, &count, arg);

		if(arg[0][0]=='#'){
			continue;
		}

		if(strcmp(arg[0],"cd")==0){
			chdir(arg[1]);
		}else{
			pid = fork();
			if(pid<0){
				printf("error");
			}else if(pid == 0){
				execvp(arg[0],arg);
			}else{
				wait(NULL);
			}
		}
	}


	close(f);
	return 0; 
}

int ReadTextLine(int fd, char str[], int max_len) {
	int i = 0;
	int j = 0; 
	int ret = 0;
	// if current position is 0, reset buffer size and pos 
	if(lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;
	while(j < max_len - 1){ 
		if(buffer_pos == buffer_size){
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFFER_SIZE); 
			buffer_pos = 0;
		}
		if(buffer_size == 0){ 
			if(j == 0)
				ret = EOF; 
			break;
		}
 	
		while(j < max_len - 2&& buffer_pos < buffer_size){
			str[j++] = buffer[buffer_pos++];
			if(str[j - 1] == '\0' || str[j - 1] == 10){
				j--; //to remove LF 
				max_len = j; //to terminate outer loop
				break; //break inner loop
			}
		}
	}
	str[j] = 0; 
	return ret;
}


void ParseCommand(char *command, int *argc, char *argv[]){
	char *p = strtok(command," ");
	int i=0;
	while(p!=NULL){
		argv[i] = p;
		i++;
		p = strtok(NULL," ");
	}
	argv[i] = NULL;
	*argc = i;
}
