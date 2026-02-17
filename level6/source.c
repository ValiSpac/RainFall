#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void(*f_ptr)(void);

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
}

void m(void)
{
    puts("Nope");
}

int main(int ac, char **av)
{
    char *a;
    char *b;
    f_ptr *f;

    a = malloc(64);
    b = malloc(4);

	*f = (void *)m;
	strcpy(a, av[1]);
	(**f)();
    return 0;
}
