// 1.考察命令mkfifo或者函数mkfifo创建命名管道
// 2.要求：创建出来的命名管道可以供两个进程通信
// 进程A 向管道当中写 “i am process A”
// 进程B 从管道当中读 并且打印到标准输出
// 3.提交要求：提交代码截图， 提交代码执行之后的截图

#include "Fifo.hpp"

int main()
{
    // 打开命名管道
    int wfd = open(Path, O_WRONLY);
    if (wfd < 0)
    {
        cerr << "open failed, errno: " << errno << ", errstring: " << strerror(errno) << endl;
        return 1;
    }

    // 写入命名管道
    string buf = "i am process A";
    ssize_t n = write(wfd, buf.c_str(), buf.size());
    if (n < 0)
    {
        cerr << "write failed, errno: " << errno << ", errstring: " << strerror(errno) << endl;
        return 2;
    }

    close(wfd);
    return 0;
}