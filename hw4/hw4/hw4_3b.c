#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv)
{
	// TO DO: open SHM_FILE for using shm_open()
	//  check if the file was successfully open
	int shm_fd = shm_open(SHM_FILE, O_CREAT|O_RDWR,0666);
	if(shm_fd==-1){	
		printf("SHM_FILE OPEN ERR");
		return 0;
	}

	int buffer_size = sizeof(KeyBuffer);

	// TO DO: map the shared memory file and receive the return address into     key_buffer
	// check if the file was successfully mapped
	KeyBuffer *key_buffer = mmap(0,buffer_size,PROT_READ|PROT_WRITE,MAP_SHARED,shm_fd,0);
	if(key_buffer==MAP_FAILED){
		printf("MAP_FAILED");
		return 0;
	}


	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();

	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;

	gotoxy(x, y);
	putchar('#');

	while(repeat){
		int oldx = x;
		int oldy = y;
		
		// TO DO: read a key from the key buffer in the shared memory
		// if the key is zero, repeat until a non-zero key is read		
		
        
        key = DeleteKey(key_buffer);
        
        if(key == 0){
            while(1){
                key = DeleteKey(key_buffer);
                gotoxy(x,y);
                if(key!=0){
                    break;
                }
            }
        }
		if(key == 'i' && y>1){
			y--;
		}else if(key == 'j' && x>1){
			x--;
		}else if(key == 'k' && y < screen_height){
			y++;
		}else if(key == 'l' && x < screen_width){
			x++;
		}

		if(key == 'c'){
			if(c == ' '){
				c = '*';
			}else if(c == '*'){
				c = ' ';
			}
		}

		if(key == 'q'){
			break;
		}
      
        // TO DO: print c at (oldx, oldy)
        gotoxy(oldx, oldy);
        printf("%c", c);


        // TO DO: print '#' at (x, y)
        gotoxy(x, y);
        printf("#");
            
	}


	clrscr();
	printf("Bye!\n");

	return 0;
}
