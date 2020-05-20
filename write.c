#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define SIZE 32

void signalHandler(int signo);
int shmid;

void main()
{
    void *shmaddr;

    if((shmid=shmget((key_t)0x0002cab7, SIZE, IPC_CREAT|0666)) == -1) {
       perror("shmid failed");
       exit(1);
    }

    /* shmid 공유메모리를 호출 프로세스 메모리 영역으로 첨부 */
    if((shmaddr=shmat(shmid, (void *)0, 0)) == (void *)-1) {
       perror("shmat failed");
       exit(1);
    }

    /* 공유메모리에 데이터 쓰기 */
    strcpy((char *)shmaddr, "test");

    /* 공유메모리를 호출 프로세스의 메모리 영역에서 분리 */
    if(shmdt(shmaddr) == -1) {
       perror("shmdt failed");
       exit(1);
    }

}

