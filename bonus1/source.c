#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc,char **argv)
{
    char buf[40];
    int res;

    res = atoi(argv[1]);
    if (res > 9)
        return 1;
    memcpy(buf , argv[2], res * 4);
    if (res == 0x574f4c46 || res == *(int *)"FLOW")
        execl("/bin/sh", "sh", 0);
    return 0;
}
