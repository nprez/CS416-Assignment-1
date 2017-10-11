// File:	my_pthread.c
// Author:	Yujie REN
// Date:	09/23/2017

// name: Nicholas Prezioso, Benjamin Cahnbley, and Marcella Alvarez
// username of iLab: njp107, bc499, and ma1143
// iLab Server: prototype

#include "my_pthread_t.h"


/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg) 
{
	my_pthread* newThread = malloc(sizeof(thread));
	ucontext_t* newContext = malloc(sizeof(ucontext_t));
	char newStack[20000];	//not sure how big this should be
	newContext->uc_stack.ss_sp = newStack;
	newContext->uc_stack.ss_size = sizeof(newStack);
	newContext->uc_link = NULL;
	newThread->tid = *thread;
	newThread->status = THREAD_READY;
	newThread->priority = 1;	//not sure what the default should be
	makecontext(newContext, *function, 1, arg);
	newThread->context = newContext;
	//put the new thread on the queue
	return 0;
};

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield() {
	return 0;
};

/* terminate a thread */
void my_pthread_exit(void *value_ptr) {
};

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr) {
	return 0;
};

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr) {
	mutex = malloc(sizeof(mutex));
	mutex->status = malloc(sizeof(enum mutex_status));
	mutex->status  = MUTEX_UNLOCKED;
	return 0;
};

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex) {
	while(mutex_status__sync_lock_test_and_set(mutex->status, MUTEX_LOCKED) == MUTEX_LOCKED);
	return 0;
};

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex) {
	mutex_status__sync_lock_test_and_set(mutex->status, MUTEX_UNLOCKED);
	return 0;
};

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex) {
	free(mutex->status);
	free(mutex);
	return 0;
};
