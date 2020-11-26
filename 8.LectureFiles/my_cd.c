// broken attempt to implement cd
// chdir() affects only this process and any it runs
// good cd program is called "getcwd.c"


#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && chdir(argv[1]) != 0) {
        perror("chdir");
        return 1;
    }
    // Any process happen in between can be executed
    // under new directroy
    // However, this is different to cd, as my_cd.c will return to original
    // directory after it has been exit.
     
    return 0;
}