#include <stdio.h>
#include <unistd.h>

int main()
{
    int count = 1;
    alarm(1);
    for (; 1; count++)
    {
        printf("count = %d\n", count);
    }

    return 0;
}

// int main()
// {
//     printf("pid is : %d\n", getpid());
//     while (1)
//     {
//         ;
//     }

//     return 0;
// }