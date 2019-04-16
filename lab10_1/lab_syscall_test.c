/*
 * lab_syscall_test.c
 *
 *  Created on: Apr 13, 2019
 *      Author: vagrant
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

/*
 * 335	common	my_syscall		__x64_sys_my_syscall
 * (I added that on arch/x86/entry/syscalls/syscal_64.tbl
 */
#define my_syscall(a,b) syscall(335, a, b)

int main(void)
{
	int p1,p2;
	p1 = -1; p2 =1;
	printf("my_syscall(%d,%d) returns %ld \n", p1, p2, my_syscall(p1,p2));
	p1 = 11; p2 =1;
	printf("my_syscall(%d,%d) returns %ld \n", p1, p2, my_syscall(p1,p2));
}
