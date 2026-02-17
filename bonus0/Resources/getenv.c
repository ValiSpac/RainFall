#include <stdio.h>

int main(int ac, char **av, char **env)
{
	printf("%p\n", getenv("PAYLOAD"));
	return 0;
}
