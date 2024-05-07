// 1.考察使用共享内存实现进程间通信， 理解共享内存原理， 考察shmget, shmat, shmdt， shmctl函数的使用， 理解共享内存的生命周期
// 2.要求：使用代码创建一个共享内存， 支持两个进程进行通信
//  进程A 向共享内存当中写 “i am process A”
//  进程B 从共享内存当中读出内容，并且打印到标准输出
// 3.提交要求：提交代码截图， 提交代码执行之后的截图

#include <sys/ipc.h>
#include <sys/shm.h>
#include "Fifo.hpp"

const char *pathname = "/home/ubuntu/Linux/test_5_4/MyShm";
const int proj_id = 0x66;

key_t GetShmKeyOrDie()
{
    key_t k = ftok(pathname, proj_id);
    if (k < 0)
    {
        std::cerr << "ftok error, errno: " << errno << ", error string: " << strerror(errno) << std::endl;
        exit(1);
    }
    return k;
}

int main()
{
    // 获取key
    key_t key = GetShmKeyOrDie();
    std::cout << "key: " << key << std::endl;

    // 创建共享内存
    int shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid < 0)
    {
        std::cerr << "shmget error, errno: " << errno << ", error string: " << strerror(errno) << std::endl;
        exit(2);
    }

    // 将共享内存和进程挂接
    void *addr = shmat(shmid, nullptr, 0);
    if ((long long int)addr == -1)
    {
        std::cerr << "shmat error" << std::endl;
        exit(3);
    }

    // 通信

    // 取消连接共享内存
    int n = shmdt(addr);
    if (n < 0)
    {
        std::cerr << "shmdt error" << std::endl;
    }

    return 0;
}