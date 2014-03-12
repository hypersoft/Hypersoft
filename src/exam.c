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

#define foo double
int main ( int argc, char** argv )
{
	printf("alignof %i: %u\n", sizeof(foo), hsAutoAlign(foo, 1));
	return (EXIT_SUCCESS);
}

