#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    key_t key;
    char *shmaddr;

    // 生成key
    key = ftok(".", 'a');
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    // 获取共享内存
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    // 连接进程地址空间
    shmaddr = shmat(shmid, NULL, 0); // 内核自己选择
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    // 读取数据并打印
    printf("Message from process A: %s\n", shmaddr);

    // 分离共享内存
    if (shmdt(shmaddr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    return 0;
}