#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
    char buf[132];
    FILE *f = fopen("/home/user/end/.pass", "r");

    memset(buf, 0, 132);
    if (!f || ac != 2)
        return(-1);
    else{
        fread(buf, 1, 66, f);
        buf[65] = 0;
        buf[atoi(av[1])] = 0;
        fread(&buf[66], 1, 65, f);
        fclose(f);

        if (strcmp(buf, av[1]) == 0)
            execl("/bin/sh", "sh", NULL);
        else
            puts(&buf[66]);
    }
	return (0);
}
