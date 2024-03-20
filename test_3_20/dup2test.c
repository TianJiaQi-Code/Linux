#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("./log", O_CREAT | O_RDWR, 0644);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    close(1);
    dup2(fd, 1);

    int i = 0;
    for (i = 0; i < 5; i++)
    {
        char buf[1024] = { 0 };
        ssize_t read_size = read(0, buf, sizeof(buf) - 1);
        if (read_size < 0)
        {
            perror("read");
            break;
        }
        printf("%s", buf);
        fflush(stdout);
    }
    return 0;
}
