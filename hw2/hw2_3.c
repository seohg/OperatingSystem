#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>


#define MAX_PATH 256

int FindFile(char *start_dir, char *target, char *path);

char new_path[MAX_PATH]="";
int len=0;
char t[MAX_PATH]="";
char temp[MAX_PATH]="";
int main(int argc, char *argv[]){

    if(argc < 3){
	    printf("Usage: %s <start_dir> <target_file>\n", argv[0]);
	    return 0;
    }
    
    char *start_dir = argv[1];
    char *target = argv[2];
    char path[MAX_PATH] = "";

    int ret = FindFile(start_dir, target, path);
    
    if(ret)
        printf("path = %s\n", path);
    else
        printf("Cannot find %s\n", target);
    return 0;
}


int FindFile(char *start_dir, char *target, char *path){

	DIR* dir_path = NULL;
	
	struct dirent* contents;


	if((dir_path=opendir(start_dir)) == NULL){
		return -1;
	}
		

	while((contents = readdir(dir_path))!=NULL){
	
		if(strcmp(contents->d_name,target)==0){

			strncpy(path,start_dir,strlen(start_dir));
			strcat(path,"/");
			strcat(path,contents->d_name);
			return 1;


		}else if(contents->d_type == 4){

			if((strncmp(contents->d_name,".",strlen("."))!=0)&&(strncmp(contents->d_name,"..",strlen(".."))!=0)){

				strncpy(new_path,start_dir,strlen(start_dir));
				
				strncpy(temp,start_dir,strlen(start_dir));
				strcat(new_path,"/");
				strcat(new_path, contents->d_name);

				if(FindFile(new_path, target, path)){
					return 1;		
				}else{
					strcpy(new_path,temp);
				}				
			}
		}
	}
	

	return 0;
	
	closedir(dir_path);
	
}



