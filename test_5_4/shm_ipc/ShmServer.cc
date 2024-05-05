#include "Comm.hpp"
#include "Fifo.hpp"

int main()
{
    // 1. 获取key
    key_t key = GetShmKeyOrDie();
    std::cout << "key: " << ToHex(key) << std::endl;

    // 2. 创建共享内存
    int shmid = CreateShm(key, defaultsize);
    std::cout << "shmid: " << shmid << std::endl;

    // 4. 将共享内存和进程进行挂接（关联）
    char *addr = (char *)ShmAttach(shmid);
    std::cout << "Attach shm success, addr: " << ToHex((uint64_t)addr) << std::endl;

    // 0. 先引入管道
    Fifo fifo;
    Sync syn;
    syn.OpenReadOrDie();

    // 可以进行通信了
    for (;;)
    {
        if (!syn.Wait())
            break;
        std::cout << "shm content: " << addr << std::endl;
    }

    ShmDetach(addr);
    std::cout << "Detach shm success, addr: " << ToHex((uint64_t)addr) << std::endl;

    // 3. 删除共享内存
    DeleteShm(shmid);

    return 0;
}