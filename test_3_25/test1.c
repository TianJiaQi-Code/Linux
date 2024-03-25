#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd = open("bite", O_WRONLY | O_CREAT, 0644);
    if (fd < 0)
    {
        perror("open");
        return 0;
    }
    
    char* buf = "i like linux!\n";
    write(fd, buf, strlen(buf));

    close(fd);
    return 0;
}
