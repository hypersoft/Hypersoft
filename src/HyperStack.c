/*

Fri Feb 28 07:38:58 CST 2014

Copyright (c) 2014, Triston J. Taylor
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "Hypersoft.h"

#define HYPER_STACK_SYSTEM

typedef struct iHyperStack {
	size_t units, count, shiftIndex;
	void ** head, ** data;
} iHyperStack;

typedef iHyperStack * HyperStack;

#define hsStackUnitsAvailable(stack) (stack->units - stack->count)
#define hsStackSize(stack) (stack->units * sizeof(void*))

#include "HyperStack.h"

size_t __HyperStackPush(HyperStack stack, size_t arguments, ...) {

	if (! arguments) return 0;

	size_t units = hsStackUnitsAvailable(stack);
	if (! units || arguments > units) {
		stack->units += (8 + arguments);
		stack->head = realloc(stack->head, hsStackSize(stack));
		stack->data = &stack->head[stack->shiftIndex];
	}

	{
		va_list ap; va_start(ap, arguments);
		register void ** data = stack->data;
		register size_t index = stack->count;
		register size_t max = index + arguments;
		while (index < max) data[index++] = va_arg(ap, void *);
		va_end(ap);
	}

	return (stack->count += arguments);

}

void * HyperStackPop(HyperStack stack) {
	if (! stack->count) return NULL;
	else return stack->data[--stack->count];
}

void * HyperStackShift(HyperStack stack) {
	if (! stack->count) return NULL;

	void * rval = stack->data[0];
	stack->data = &stack->head[++stack->shiftIndex]; stack->count--;

	if (stack->shiftIndex == 16 ) {
		stack->units -= 8;
		void ** head = malloc(hsStackSize(stack));
		stack->data = hsCopyMemory(&head[(stack->shiftIndex = 7)],
			stack->data,
				stack->count
		); free(stack->head);
		stack->head = head;
	}

	return rval;
}

size_t __HyperStackUnshift(HyperStack stack, size_t arguments, ...) {

	if (! arguments) return 0;

	size_t
		units = stack->units,
			used = stack->count,
				shift = stack->shiftIndex;

	size_t slotsNeeded = (arguments > (units - used))?arguments + units - 1 : 0;

	if (slotsNeeded) {
		printf("slots needed: %u\n", slotsNeeded);
		stack->units = slotsNeeded;
		void
			** head = malloc(hsStackSize(stack)),
				** data = &head[shift+arguments];
		if (used) hsCopyMemory(data, stack->data, used);
		free(stack->head); stack->head = head;
		stack->data = data;
		stack->shiftIndex += arguments;
	}

	{
		va_list ap;	va_start(ap, arguments);
		stack->shiftIndex -= arguments;
		stack->data = &stack->head[stack->shiftIndex];
		register void ** data = stack->data;
		register size_t index = 0;
		register size_t max = arguments;
		while (index < max) data[index++] = va_arg(ap, void *);
		va_end(ap);
	}

	return (stack->count += arguments);

}

HyperStack HyperStackSlice(HyperStack stack, int64_t start, int64_t end) {

	{
		register size_t max = stack->count;
		if (start < 0) start = max + start;
		if (start < 0) return NULL; /* we tried... */
		else if (start >= max) return NULL;

		if (end < 0) end = max + start;
		if (end < 0) return NULL; /* we tried ... */
		else if (end > max || ! end) end = max;
	}

	if (start > end) return NULL;

	size_t count = end - start, units = 4 + count;

	HyperStack slice = calloc(1, sizeof(iHyperStack));

	slice->head = malloc(units * sizeof(void*));
	slice->shiftIndex = 3;
	slice->count = count;
	slice->units = units;
	slice->data = hsCopyMemory(&slice->head[3], &stack->data[start], count);

	return slice;

}

void * HyperStackPeek(HyperStack stack, size_t index) {
	if (! stack->count) return NULL;
	if (index < stack->count) return stack->data[index];
	return NULL;
}

void * HyperStackPoke(HyperStack stack, size_t index, void * value) {
	void * rval = NULL;
	if (! stack->count) return NULL;
	if (index < stack->count)
		rval = stack->data[index], stack->data[index] = value;
	return rval;
}

HyperStack hsCreateStack() {
	HyperStack stack = calloc(1, sizeof(iHyperStack));
	stack->head = malloc(8*sizeof(void*));
	stack->shiftIndex = 3;
	stack->units = 8;
	stack->data = &stack->head[3];
	return stack;
}

void * hsFreeStack(HyperStack stack) {
	free(stack->head), free(stack);
	return NULL;
}
