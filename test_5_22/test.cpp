#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
    while (true)
    {
        cout << "I am a process, I am waiting signal!" << endl;
        sleep(1);
    }
    return 0;
}
