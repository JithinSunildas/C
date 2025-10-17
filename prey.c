#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    signal(SIGINT, SIG_IGN);

    char name[20];
    int result = gethostname(name, 20);
    printf("%s\n", name);

    printf("Process id: %d\n", getpid());

    while (1) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    return 0;
}
