#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("myfile", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    
    const char* msg = "hello open!\n";
    char buf[1024];
    while (1)
    {
        ssize_t s = read(fd, buf, strlen(msg)); // 类比write
        if (s > 0)
        {
            printf("%s", buf);
        }
        else
        {
            break;
        }
    }

    close(fd);
    return 0;
}
