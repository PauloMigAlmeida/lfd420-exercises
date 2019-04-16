/*
 * main.c
 *
 *  Created on: Apr 16, 2019
 *      Author: CORP\paulo
 */

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

int global = 0;

int clone_fn(void *__arg);
void errExit(char* message);

int main(void)
{
	const int STACK_SIZE = 65536;       /* Stack size for cloned child */
	char *stack;                        /* Start of stack buffer area */
	char *stackTop;                     /* End of stack buffer area */

	/* Allocate stack for child */
	stack = malloc(STACK_SIZE);
	if (stack == NULL)
		errExit("malloc");

	printf("main :: Init\n");
	for (int i = 0; i < 10; i++) {
		stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */
		if(clone(clone_fn ,stackTop ,CLONE_VM | SIGCHLD | CLONE_PTRACE, &i)  == -1)
			errExit("clone");
		sleep(10);
	}
	return 0;
}

int clone_fn(void *__arg)
{
	int* i = (int*)__arg;
	int* seed = malloc(sizeof(int*));
	memcpy(seed, i, sizeof(int));

	printf("clone_fn :: child:  PID=%ld PPID=%ld\n", (long) getpid(), (long) getppid());


	printf("clone_fn :: [Thread: %d] :: init\n", *i);
	printf("clone_fn :: [Thread: %d] :: Pre-mod Global value is: %d\n", *i, global);
	global += rand_r((unsigned int *)seed);
	printf("clone_fn :: [Thread: %d] :: Post-mod Global value is: %d\n", *i, global);
	printf("clone_fn :: [Thread: %d] :: finish\n", *i);

	free(seed);
	return 0;
}

void errExit(char* message)
{
	printf("[errExit] :: Deu ruim no(a) %s. errono: %d\n", message, errno);
	exit(-1);
}

