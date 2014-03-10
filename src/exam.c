/*
 * File:   exam.c
 * Author: Triston J. Taylor <pc.wiz.tt@gmail.com>
 *
 * Created on February 28, 2014, 9:45 AM
 */

#include "Hypersoft.h"
#include "HyperVariant.h"
#include "HyperStack.h"

int32_t examForEach (HyperSoftVariant t, void *v, void *p) {
	char c = utf8val(v);
	putchar(c);
}

int main ( int argc, char** argv )
{
	HyperStack stack = hsCreateStack();
	HyperStackUnshift(stack, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
	HyperStack slice = HyperStackSlice(stack, 0, 4);
	printf("pops: %u\n", HyperStackPop(slice));
	hsFreeStack(stack); hsFreeStack(slice);
	return (EXIT_SUCCESS);
}

