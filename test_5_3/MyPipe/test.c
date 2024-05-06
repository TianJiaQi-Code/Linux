#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 1.考察pipe函数的使用， 以及对pipe函数参数的理解，同时考察对文件描述符的理解
// 2.要求：先创建管道， 进而创建子进程， 父子进程使用管道进行通信
// 父进程向管道当中写“i am father”，
// 子进程从管道当中读出内容, 并且打印到标准输出
// 3.提交要求：提交代码截图， 提交代码执行之后的截图

// father
void writer(int wfd)
{
    const char *str = "i am father";
    ssize_t n = write(wfd, str, strlen(str));
    if (n != -1)
    {
        printf("father write\n");
    }
    else
    {
        printf("err\n");
    }

    close(wfd);
}

// child
void reader(int rfd)
{
    char buffer[128];
    ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
    if (n > 0)
    {
        printf("child get a message: %s, n: %ld\n", buffer, n);
    }
    else if (n == 0)
    {
        printf("done\n");
    }
    else
    {
        printf("err\n");
    }

    close(rfd);
}

int main()
{
    // 创建管道
    int pipefd[2];
    // fd[0]表示读端，fd[1]表示写端
    int n = pipe(pipefd);
    if (n < 0) // 创建失败
    {
        return 1;
    }

    // 创建子进程
    pid_t id = fork();

    if (id == 0)
    {
        // child: r
        close(pipefd[1]);
        reader(pipefd[0]);
        exit(0);
    }

    // father: w
    close(pipefd[0]);
    writer(pipefd[1]);

    // 等待子进程退出
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        printf("exit code: %d, exit signal: %d\n", WEXITSTATUS(status), status & 0x7F);
    }

    return 0;
}