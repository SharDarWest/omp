#include <omp.h>
#include <cstdio>


 main(int argc, char *argv[])  {

 int   i, n, chunk;
 float a[100], b[100], result;

 /* Some initializations */
 n = 1000;
 chunk = 10;
 result = 0.0;
 for (i=0; i < n; i++) {
   a[i] = i * 1.0;
   b[i] = i * 2.0;
   }

 #pragma omp parallel for      \  
   default(shared) private(i)  \  
   schedule(static,chunk)      \  
   reduction(+:result)  

   for (i=0; i < n; i++) {
     int threadID=omp_get_thread_num();
     printf("Before: i=%d, thread=%d, result=%.1f, a[i]=%.1f, b[i]=%.1f\n", i, threadID, result, a[i], b[i]);
     result = result + (a[i] + b[i]);
     printf("After: i=%d, thread=%d, result=%.1f\n", i, threadID, result);
   }

 printf("Final result= %f\n",result);

 }
