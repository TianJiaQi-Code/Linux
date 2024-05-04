#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// child
void writer(int wfd)
{
    const char *str = "hello father, I am child";
    char buffer[128];
    int cnt = 0;
    pid_t pid = getpid();
    while (1)
    {
        sleep(1);
        char c = 'A';
        write(wfd, &c, 1);
        cnt++;

        printf("cnt: %d\n", cnt);
    }
    close(wfd);
}

// father
void reader(int rfd)
{
    char buffer[1024];
    int cnt = 10;
    while (1)
    {
        ssize_t n = read(rfd, buffer, sizeof(buffer) - 1);
        if (n > 0)
            printf("father get a message: %s, n: %ld\n", buffer, n);
        else if (n == 0)
        {
            printf("read pipe done, read file done!\n");
            break;
        }
        else
            break;

        cnt--;
        if (cnt == 0)
            break;
    }
    close(rfd);
    printf("read endpoint close!\n");
}

int main()
{
    printf("PIPE_BUF: %d\n", _PC_PIPE_BUF);

    // 1.
    int pipefd[2];
    int n = pipe(pipefd);
    if (n < 0)
        return 1;

    //                                       read       write
    printf("pipefd[0]: %d, pipefd[1]: %d\n", pipefd[0], pipefd[1]); // 3, 4

    // 2.
    pid_t id = fork();
    if (id == 0)
    {
        // child: w
        close(pipefd[0]);
        writer(pipefd[1]);
        exit(0);
    }

    // father: r
    close(pipefd[1]);
    reader(pipefd[0]);

    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        printf("exit code: %d, exit signal: %d\n", WEXITSTATUS(status), status & 0x7F);
    }

    return 0;
}