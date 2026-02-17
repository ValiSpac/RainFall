#include <stdio.h>
#include <stdlib.h>

int m = 0;

int v(void)
{
    char    buf[512];

    fgets(buf, 512, stdin);
    printf(buf);
    if (m == 64)
    {
        fwrite("Wait what?!\n", 12, 1, stdout);
        system("/bin/sh");
    }
    return (0);
}

int main(void)
{
    v();
    return (0);
}
