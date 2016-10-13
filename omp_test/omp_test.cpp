#include <iostream>
#include <cstdio>
#include <string>
#include "omp.h"

using namespace std;

void repeatString(int times, int threadID) {
    int localThreadID;
    for (int index=0; index<times; ++index) {
        localThreadID=omp_get_thread_num();
        if (localThreadID != threadID) {
            printf("Thread IDs do not match! main thread ID: %d, local thread ID: %d", threadID, localThreadID);
        }
        printf("Hello from thread %d, loop %d\n", threadID, index);
    }
}


int main (int argc, char *argv[])
{
    
    #pragma omp parallel for
    for (int n=0; n<20; ++n) {
        int threadID=omp_get_thread_num();
        repeatString(30, threadID);
    }
    return(0);
}

