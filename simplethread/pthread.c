#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>
#include <sys/utsname.h>
#include <string.h>
#include "uname.h"

#define NUM_THREADS 12

typedef struct
{
    int threadIdx;
} threadParams_t;

// POSIX thread declarations and scheduling attributes
//
pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];


void *counterThread(void *threadp)
{
    int sum=0, i;
    threadParams_t *threadParams = (threadParams_t *)threadp;

    syslog(LOG_INFO, "Hello World from Thread!");

    for(i=1; i < (threadParams->threadIdx)+1; i++)
        sum=sum+i;
 
    printf("Thread idx=%d, sum[0...%d]=%d\n", 
           threadParams->threadIdx,
           threadParams->threadIdx, sum);
    
    return NULL;
}


int main (int argc, char *argv[])
{
   int rc;
   int i;
   struct utsname buffer;

   openlog("[COURSE:1][ASSIGNMENT:1]", LOG_PID | LOG_CONS, LOG_USER);

   if (uname(&buffer) == -1) {
   //    syslog(LOG_ERR, "uname failed: %s", strerror(errno));
       printf("FAIL");
       closelog();
       return EXIT_FAILURE;
   }

   //syslog(LOG_INFO, "%s %s %s %s %s", buffer.sysname, buffer.nodename, 
    //       buffer.release, buffer.version, buffer.machine);
   
   log_uname();

   syslog(LOG_INFO, "Hello World from Main!");

   for(i=0; i < NUM_THREADS; i++)
   {
       threadParams[i].threadIdx=i;

       pthread_create(&threads[i],   // pointer to thread descriptor
                      (void *)0,     // use default attributes
                      counterThread, // thread function entry point
                      (void *)&(threadParams[i]) // parameters to pass in
                     );

   }

   for(i=0;i<NUM_THREADS;i++)
       pthread_join(threads[i], NULL);

   printf("TEST COMPLETE\n");
   closelog();

   return 0;
}
