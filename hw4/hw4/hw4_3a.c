#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv[])
{
	// TO DO: open SHM_FILE for using shm_open()
	int shm_fd = shm_open(SHM_FILE, O_CREAT|O_RDWR, 0666);

	//	check if the file was successfully open
	if(shm_fd == -1){
		printf("SHM_FILE OPEN ERR");
		return 0;
	}
	int buffer_size = sizeof(KeyBuffer);

	// TO DO: set size of the shared memory by buffer_size
	ftruncate(shm_fd,buffer_size);

	KeyBuffer *key_buffer = NULL;
	// TO DO: map the shared memory file and receive the return address into key_buffer
	key_buffer = mmap(0,buffer_size,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);

	//	check if the file was successfully mapped
	if(key_buffer==MAP_FAILED){
		printf("MAP_FAILED");
		return 0;
	}

	// TO DO: initialize the key buffer in the shared memory
	InitKeyBuffer(key_buffer);

	clrscr();

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit hw4_3b, ESC: quit both\n");

	while(1){
		gotoxy(1, 2);
		printf("Input a key: ");
		int key = getch();

		/* TO DO: implement the following action
			if key is ESC (ASCII 27), insert 'q' into the key buffer and break the loop
			otherwise, insert the key into the key buffer.

		*/
		if(key == 27){
			InsertKey(key_buffer,'q');
			break;
		}else{
			InsertKey(key_buffer,key);
		}

		DisplayKeyBuffer(1, 2, key_buffer);
	}

	// TO DO: unmap and unlink the shared memory block
	munmap(key_buffer,buffer_size);
	shm_unlink(SHM_FILE);

	clrscr();
	printf("Bye!\n");

	return 0;
}

