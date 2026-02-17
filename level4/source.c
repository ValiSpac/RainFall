#include <stdio.h>
#include <stdlib.h>

int m = 0;

void p(char *arg)
{
    printf(arg);
}

void n(void)
{
    char buf[512];

    fgets(buf, 520, stdin);
    p(buf);
    if(m == 16930116)
        system("/bin/cat /home/user/level5/.pass");
}

int main()
{
    n();
    return 0;
}

