#include "Comm.hpp"
#include "Fifo.hpp"

int main()
{
    key_t key = GetShmKeyOrDie();
    std::cout << "key: " << ToHex(key) << std::endl;

    int shmid = GetShm(key, defaultsize);
    std::cout << "shmid: " << shmid << std::endl;

    char *addr = (char *)ShmAttach(shmid);
    std::cout << "Attach shm success, addr: " << ToHex((uint64_t)addr) << std::endl;

    memset(addr, 0, defaultsize);
    Sync syn;
    syn.OpenWriteOrDie();

    // 可以进行通信了
    for (char c = 'A'; c <= 'Z'; c++) // shm没有使用系统调用
    {
        addr[c - 'A'] = c;
        syn.Wakeup();
        sleep(1);
    }

    ShmDetach(addr);
    std::cout << "Detach shm success, addr: " << ToHex((uint64_t)addr) << std::endl;
    sleep(5);

    return 0;
}