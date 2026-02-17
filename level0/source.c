#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define _GNU_SOURCE

int main(int argc, char **argv)
{
    __gid_t gid;
    __uid_t uid;
    char    sh[2];

    if (atoi(argv[1]) == 423){
        sh[0] = strdup("/bin/sh");
        sh[1] = '\0';
        gid = getgid();
        uid = getuid();
        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);

        execv("/bin/sh", sh);
    }
    else
        fwrite("No !\n", 5, 1, stderr);
    return 0;
}
