#include <stdio.h>

#include "elapsed_time.h"

int main() {
    double t1 = cpu_time();
    
    // Simulate some processing with a sleep
    for (volatile int i = 0; i < 100000000; ++i);
    
    double t2 = cpu_time();
    printf("elapsed time: %.6f seconds\n",t2 - t1);

    return 0;
}