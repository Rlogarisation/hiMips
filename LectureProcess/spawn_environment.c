// simple example of using environment variable to change program behaviour
// run date -to print time
// Perth time printed, due to TZ environment variable
/*
z5206267@corelli:~/COMP1521/LectureProcess$ ./spawn_environment 
Tue Nov 17 19:08:36 AWST 2020
/bin/date exit status was 0
*/
#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    char *date_argv[] = { "/bin/date", NULL };
    char *date_environment[] = { "TZ=Australia/Perth", NULL };
    // print time in Perth
    if (posix_spawn(&pid, "/bin/date", NULL, NULL, date_argv,
                    date_environment) != 0) {
        perror("spawn");
        return 1;
    }

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    printf("/bin/date exit status was %d\n", exit_status);
    return 0;
}