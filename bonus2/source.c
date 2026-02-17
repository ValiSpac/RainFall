#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language;

void greetuser(char *str)
{
    char buf[72];
    if (!language)
        memcpy(buf, "Hello ", 7);
    if (language == 1)
        memcpy(buf, "Hyvää päivää ", 14);
    if (language == 2)
        memcpy(buf, "Goedemiddag! ", 14);
    strcat(buf, str);
    puts(buf);
}

int main(int ac, char **av)
{
    char buf[72];
    char *env = NULL;

    if (ac != 3)
        return 1;

    memset(buf, 0, 72);
    strncpy(buf, av[1], 40);
    strncpy(buf + 40, av[2], 32);
    env = getenv("LANG");
    if (env){
        if (memcmp(env, "fi", 2) == 0)
            language = 1;
        else if (memcmp(env, "nl", 2) == 0)
            language = 2;
    }
    greetuser(buf);
    return 0;
}

