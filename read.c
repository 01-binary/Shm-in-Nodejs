#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE 32

int main() {
	int shmid;
	key_t key;
	void *shmaddr;

	key=0x0002cab7;


    if((shmid=shmget(key, KEY_SIZE, IPC_CREAT|0666)) == -1) {

       perror("shmid failed");

       exit(1);

    }



    if((shmaddr=shmat(shmid, (void *)0, 0)) == (void *)-1) {

       perror("shmat failed");

       exit(1);

    }

	printf("data read from shared memory : %s\n", (char *)shmaddr);
	
	exit(0);
}

