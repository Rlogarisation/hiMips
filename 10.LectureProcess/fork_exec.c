// simple example of classic fork/exec
// run date --utc to print current UTC
//
// use posix_spawn instead

// This is the old method to run /bin/data by using fork(),
// and runing exec in child, wait in parent process.
// The safest and quickest is use function posix_spawn().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
         perror("fork"); // print why fork failed
    } else if (pid == 0) { // child

        char *date_argv[] = {"/bin/date", "--utc", NULL};

        execv("/bin/date", date_argv);

        perror("execvpe"); // print why exec failed

    } else { // parent

        int exit_status;
        if (waitpid(pid, &exit_status, 0) == -1) {
            perror("waitpid");
            exit(1);
        }
        printf("/bin/date exit status was %d\n", exit_status);
    }

    return 0;
}