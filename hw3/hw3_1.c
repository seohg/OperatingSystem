#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i = 0;
	float delay = -1;
	float elapsed = 0;
	time_t current_t;
	struct tm *d, *start_d, *end_d;
	struct timeval start_time, end_time;


	if(argv[1]==NULL){
		printf("Usage: %s <delay_time>\n",argv[0]);
		return 0;
	}else{
		delay = atof(argv[1]);
	}

	current_t = time(NULL);
	d = localtime(&current_t);	

	printf("current date = %d/%d/%d\n",d->tm_year+1900, d->tm_mon+1, d->tm_mday);
	printf("current time = %d:%d:%d\n\n",d->tm_hour, d->tm_min, d->tm_sec);

	gettimeofday(&start_time, NULL);
	start_d = localtime(&start_time.tv_sec);
	
	printf("wating for %f sec using usleep()\n\n",delay);
	printf("start_time = (%ld %ld), %d:%d:%d\n",start_time.tv_sec, start_time.tv_usec,start_d->tm_hour, start_d->tm_min, start_d->tm_sec);

	usleep(delay*1000*1000);
	gettimeofday(&end_time, NULL);
	end_d = localtime(&end_time.tv_sec);


	printf("end_time = (%ld %ld), %d:%d:%d\n",end_time.tv_sec, end_time.tv_usec,end_d->tm_hour, end_d->tm_min, end_d->tm_sec);

	elapsed = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_usec-start_time.tv_usec)/1000000.0);
	
	printf("elapsed time = %fsec\n",elapsed);
	
	return 0;
}
