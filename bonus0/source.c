#include <stdio.h>
#include <unistd.h>
#include <string.h>

void p(char *arg, char *c)
{
    char buf[4096];

    puts(c);
    read(0, buf, 4096);
    *strchr(buf, 10) = 0;
    strncpy(arg, buf, 20);
}

void pp(char *arg)
{
    char    buf[20];
    char    buf2[20];

    p(buf, "-");
    p(buf2, "-");
    strcpy(arg, buf);
    int len = strlen(arg);
    arg[len] = ' ';
    strcat(arg, buf2);
}

int main(void)
{
    char var[42];

    pp(var);
    puts(var);

    return 0;
}
