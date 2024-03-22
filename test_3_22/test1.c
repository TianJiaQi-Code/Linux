#include <stdio.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("./bite", "w");
    if (!fp)
    {
        printf("fopen error\n");
        return 1;
    }
    char* msg = "linux so easy!\n";
    fwrite(msg, strlen(msg), 1, fp);

    fclose(fp);
    return 0;
}
