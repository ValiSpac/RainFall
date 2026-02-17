#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*p(void)
{
    char buf[64];
    void *retaddr;

    fflush(stdout);
    gets(buf);
    retaddr = __builtin_return_address (0);
    if (((unsigned int)retaddr & 0xb0000000) == 0xb0000000)
    {
        printf("%p\n", retaddr);
        exit(1);
    }
    puts(buf);
    return (strdup(buf));
}

int main(void)
{
    p();
    return (0);
}
