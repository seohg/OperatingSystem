#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

// global variables
char buffer[BUFFER_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len)
{
	int i = 0;
	int j = 0;
	int ret = 0;
	// if current position is 0, reset buffer size and pos
	if(lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;
	while (j < max_len - 1){
	
   		if (buffer_pos == buffer_size){
       			 buffer[0] = 0;
       			 buffer_size = read(fd, buffer, BUFFER_SIZE);
      	 		 buffer_pos = 0;
		 }
		if (buffer_size == 0){
			if (j == 0)
				ret = EOF;
	        	break;
		}
	    	while (j < max_len - 2 && buffer_pos < buffer_size){
        		str[j++] = buffer[buffer_pos++];
			if(str[j - 1] == '\0' || str[j - 1] == 10){
				j--; // to remove LF
				max_len = j; // to terminate outer loop
				break; // break inner loop
			}
		}
	}
	str[j] = 0;
	return ret;
}

int main(){
	int f1,f1_2,f2,f3;
	char line[300];

	char str1[150];
	char str2[150];

	char core[150], modelName[150], memory[150];
	float avg[3];

	f1 = open("/proc/cpuinfo",O_RDONLY);	
	f1_2 = open("/proc/cpuinfo", O_RDONLY);
	f2 = open("/proc/meminfo",O_RDONLY);
	f3 = open("/proc/loadavg",O_RDONLY);


	while(ReadTextLine(f1,line,BUFFER_SIZE)!=EOF){
		sscanf(line,"%[^:]:%[^\n]",str1, str2);

		if(strncmp(str1,"cpu cores",strlen("cpu cores"))==0){
			strcpy(core, str2);
			break;
		}
	}


	while(ReadTextLine(f1_2,line,BUFFER_SIZE)!=EOF){
		sscanf(line,"%[^:]:%[^\n]",str1, str2);

		if(strncmp(str1,"model name",strlen("model name"))==0){
			strcpy(modelName, str2);
			break;
		}
	}


	while(ReadTextLine(f2,line,BUFFER_SIZE)!=EOF){
		sscanf(line,"%[^:]:%[^\n]",str1, str2);

		if(strncmp(str1,"MemTotal",strlen("MemTotal"))==0){
			strcpy(memory, str2);
			break;
		}
	}


	while(ReadTextLine(f3,line,BUFFER_SIZE)!=EOF){
		float a[5];
		sscanf(line,"%f %f %f %f %f",&a[0], &a[1], &a[2], &a[3], &a[4]);
		avg[0] = a[0];
		avg[1] = a[1];
		avg[2] = a[2];

	}

	
	printf("# of processor cores = %s\n",core);
	printf("CPU model = %s\n",modelName);
	printf("MemTotal = %s\n", memory);
	printf("loadavg1 = %.6f, loadavg5 = %.6f, loadavg = %.6f\n", avg[0], avg[1], avg[2]);
}
