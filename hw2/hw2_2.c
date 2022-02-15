#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>


int main(){
	DIR* path = NULL;
	char curdir[1024];
	
	struct dirent* contents;

	getcwd(curdir, 1024);
	
	if((path=opendir(curdir)) == NULL){
		return -1;
	}
	
	while((contents = readdir(path))!=NULL){
		if(contents->d_type == 4){
			printf("%s [directory]\n",contents->d_name);
		}else{
			printf("%s\n",contents->d_name);	
		}
	}

	return 0;
}

