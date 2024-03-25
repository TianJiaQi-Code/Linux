#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("bite", O_RDONLY, 0644);
    if (fd < 0)
    {
        perror("open");
        return 0;
    }
    char* msg = "i like linux!\n";
    char buf[128];
    ssize_t s = read(fd, buf, strlen(msg));
    if (s > 0)
    {
        printf("%s", buf);
    }

    close(fd);
    return 0;
}
