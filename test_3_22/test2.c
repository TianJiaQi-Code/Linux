#include <stdio.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("./bite", "r");
    if (!fp)
    {
        printf("fopen error\n");
        return 1;
    }
    char buf[128];
    char* msg = "linux so easy!\n";

    ssize_t s = fread(buf, 1, strlen(msg), fp);
    if (s > 0)
    {
        buf[s] = 0;
        printf("%s", buf);
    }

    return 0;
}
