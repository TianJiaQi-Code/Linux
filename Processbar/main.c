#include "processbar.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// 模拟文件大小
#define FILESIZE (1024 * 1024 * 1024)

// 模拟一种场景，表示一种下载任务
void download(callback_t cb)    // 回调函数的形式
{
    srand(time(NULL) ^ 1023);   // 这样写只是为了让随机数更随机
    int total = FILESIZE;
    while (total)
    {
        usleep(10000);  // 下载动作
        int one = rand() % (1024 * 1024);  // 一次下载的大小
        total -= one;
        if (total < 0)
        {
            total = 0;
        }

        // 当前的进度是多少？
        int download = FILESIZE - total;
        double rate = (download * 1.0 / FILESIZE) * 100.0;
        cb(rate);
    }
}

int main()
{
    //process();
    download(process_flush);

    return 0;
}
