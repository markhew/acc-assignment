/* BeginSourceFile args.c */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include	"acc.h"

struct pthreadArgs
{
	int arg1, arg2, ap;

	/* data */
};

typedef struct pthreadArgs strPT;


void *thread_function(void *);
pthread_t create_thread();
int
main(int argc, char **argv)
{
	pthread_t threadID;
	void* result;
	threadID = create_thread();
	printf("main : Hello from your creator! My ID is %d \n", pthread_self());
	printf("I have just created a thread with ID %d \n", threadID);
	pthread_join(threadID, &result);
	printf("Result in main: %d \n", (int)result);
	exit(0);

}

pthread_t 
create_thread()
{
	pthread_t threadID;
	int ap;
	int error;

	strPT *s;
	s = (strPT*) malloc(sizeof(strPT));
	s->arg1 = 10;
	s->arg2 = 5;
	s->ap = pthread_self();

	ap = pthread_self();
	printf("create_thread : Hello from your creator! My ID is %d \n", ap);
	error = pthread_create(&threadID, NULL, thread_function, (void *) s);
	if (error != 0)
	{
		printf("pthread_create failed due to %d\n", error);
		exit (1);
	}
	//sleep(2);  Line A
	return(threadID);
	
}
void *
thread_function(void *arg)
{
	sleep(2);//  Line B

	strPT* argp;
	argp = (strPT*)arg;

	int result = argp->arg1 + argp->arg2;

	printf("My creator ID is %d \n", argp->ap);
	printf("My thread ID: %d \n", pthread_self());
	printf("Result in thread: %d \n", result);

	//void* res = (void*)result;
	return (void *) result;
}
/* EndSourceFile */

