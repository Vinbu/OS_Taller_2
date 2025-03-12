#include <stdio.h>
#include <unistd.h>

long cpu_main() 
{
    long num_procs = sysconf(_SC_NPROCESSORS_ONLN);
    if (num_procs > 0 ){
        return num_procs;
    }
    else {
            printf("It won´t be possible to obtain the number of processors\n");
    }
    return 0;
}