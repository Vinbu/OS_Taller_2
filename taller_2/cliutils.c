#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sigint_count = 0;

void reset_sigint_count(int signo) {
    sigint_count = 0;
}

void sigterm_handler(int signo) {
    if (sigint_count == 0) {
        printf("\n Are you sure that you want to stop the program?\n");
        sigint_count++;
        alarm(5);
    } else {
        printf("\n Signal SIGTERM %d catch.\n", signo);
        exit(0);
    }
}

int main(int argc, char **argv) {
    int pflag = 0;
    int index;
    int c;

    opterr = 0;

    if (signal(SIGINT, sigterm_handler) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    if (signal(SIGALRM, reset_sigint_count) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while ((c = getopt(argc, argv, "p")) != -1)
        switch (c) {
        case 'p':
            pflag = 1;
            break;
        case '?':
            if (optopt == 'c')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            return 1;
        default:
            abort();
        }

    if (pflag) {
        long num_procs = cpu_main();
        for (int i = 0; i < 10; i++) {
            printf("loading for %d secs...\n", i);
            sleep(1);
        }
        printf("Number of processors: %ld\n", num_procs);
    }

    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return 0;
}