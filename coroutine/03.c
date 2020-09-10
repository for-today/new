#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ucontext.h>

ucontext_t ctx_main, ctx_f1, ctx_f2;

void fun1( void ) {
	printf("fun1() start\n");
	swapcontext(&ctx_f1, &ctx_f2);
	printf("fun1() end\n");
}

void fun2( void ) {
	printf("fun2() start\n");
	swapcontext(&ctx_f2, &ctx_f1);
	printf("fun2() end\n");
}

int main( void ) {
	char stack1[1024*8];
	char stack2[1024*8];
	
	getcontext(&ctx_f1);
	getcontext(&ctx_f2);

	ctx_f1.uc_stack.ss_sp    = stack1;
	ctx_f1.uc_stack.ss_size  = 1024*8;
	ctx_f1.uc_stack.ss_flags = 0;
	ctx_f1.uc_link = &ctx_f2;
	makecontext(&ctx_f1, fun1, 0);

	ctx_f2.uc_stack.ss_sp    = stack2;
	ctx_f2.uc_stack.ss_size  = 1024*8;
	ctx_f2.uc_stack.ss_flags = 0;
	ctx_f2.uc_link = &ctx_main;
	makecontext(&ctx_f2, fun2, 0);

	swapcontext(&ctx_main, &ctx_f1);

	printf("main exit\n");
}

