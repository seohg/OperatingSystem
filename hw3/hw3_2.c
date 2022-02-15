#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char *argv[]) {
	
	struct utsname uts_name;
	struct sysinfo sys_info;
	struct stat s;
	struct tm *d;
	if(argv[1]==NULL){

		printf("User and Process info:\n");
		printf("\tgetuid() = %d\n",getuid());
		printf("\tgetpid() = %d\n",getpid());
		printf("\tgetppid() = %d\n",getppid());
		
		uname(&uts_name);		
		printf("\nKernel info:\n");
		printf("\tsysname = %s\n",uts_name.sysname);
		printf("\tnodename = %s\n",uts_name.nodename);
		printf("\trelease = %s\n",uts_name.release);
		printf("\tversion = %s\n",uts_name.version);
		printf("\tmachine = %s\n",uts_name.machine);
		
		sysinfo(&sys_info);
		printf("\nSystem info:\n");
		printf("\tuptime = %ld\n",sys_info.uptime);	
		printf("\ttotalram = %lu\n",sys_info.totalram);
		printf("\tfreeram = %lu\n",sys_info.freeram);
		printf("\tprocs = %hu\n\n",sys_info.procs);
	
	}else{
		if(access(argv[1],F_OK)!=0){
			printf("%s is not exist", argv[1]);
			return 0;
		}

		printf("Permission of file %s\n",argv[1]);		
		printf("\tPermssion to read: %d\n",access(argv[1],R_OK)+1);
		printf("\tPermssion to write: %d\n",access(argv[1],W_OK)+1);
		printf("\tPermssion to execute: %d\n\n",access(argv[1],X_OK)+1);
		
		printf("stat of file %s\n",argv[1]);
		if(stat(argv[1],&s)==-1){
			printf("stat error");
			return 0;
		}
		printf("\tst_dev = %lu\n",s.st_dev);
		printf("\tst_ino = %lu\n",s.st_ino);
		printf("\tst_mode = %o (octal)\n",s.st_mode);
		printf("\tst_uid = %u\n",s.st_uid);
		printf("\tst_gid = %u\n",s.st_gid);
		printf("\tst_size = %ld\n",s.st_size);
		d = localtime(&s.st_atime);
		printf("\tst_atime = %d/%d/%d %d:%d:%d\n",d->tm_year+1900,d->tm_mon+1,d->tm_mday,d->tm_hour,d->tm_min,d->tm_sec);
		d = localtime(&s.st_mtime);
		printf("\tst_mtime = %d/%d/%d %d:%d:%d\n",d->tm_year+1900,d->tm_mon+1,d->tm_mday,d->tm_hour,d->tm_min,d->tm_sec);
		d = localtime(&s.st_ctime);
		printf("\tst_ctime = %d/%d/%d %d:%d:%d\n",d->tm_year+1900,d->tm_mon+1,d->tm_mday,d->tm_hour,d->tm_min,d->tm_sec);
	}


/*
	int i = 0;
	printf("%d arguments\n", argc); for(i = 0; i <= argc; i++){
	printf("argv[%d] = %s\n", i, argv[i]); }
*/


	return 0; 
}


