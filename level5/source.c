#include <stdio.h>
#include <stdlib.h>

void o(void)
{
    system("/bin/sh");
    exit(1);
}

int n(void)
{
    char buf[512];
    fgets(512, buf, stdin);
    printf(buf);
    exit(1);
}

int main()
{
    n();
    return 0;
}
