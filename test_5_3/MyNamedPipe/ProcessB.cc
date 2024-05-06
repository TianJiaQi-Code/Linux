#include "Fifo.hpp"

int main()
{
    // 创建命名管道
    // 一个进程创建，另一个直接使用
    Fifo fifo(Path);

    int rfd = open(Path, O_RDONLY);
    if (rfd < 0)
    {
        cerr << "open failed, errno: " << errno << ", errstring: " << strerror(errno) << endl;
        return 1;
    }

    // 如果我们的写端没打开，先读打开，open的时候就会阻塞，直到把写端打开，读open才会返回
    cout << "open success" << endl;

    // 从命名管道读取
    char buffer[128];
    ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        buffer[n] = 0;
        cout << "process B read: " << buffer << endl;
    }
    else if (n == 0)
    {
        cout << "quit" << endl;
    }
    else
    {
        cout << "err" << endl;
    }

    close(rfd);
    return 0;
}