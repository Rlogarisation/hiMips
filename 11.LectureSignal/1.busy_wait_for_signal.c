// simple example of catching a signal

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    printf("signal number %d received\n", signum);
}

int main(void) {
    struct sigaction action = {.sa_handler = signal_handler};
    sigaction(SIGUSR1, &action, NULL);

    printf("I am process %d waiting for signal %d\n", getpid(), SIGUSR1);

    // loop waiting for signal
    // bad consumes CPU/electricity/battery
    // sleep would be better

    while (1) {
    }
}