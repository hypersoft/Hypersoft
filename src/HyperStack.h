/*

Fri Feb 28 07:39:02 CST 2014

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

#ifndef HYPERSTACK_H
#define HYPERSTACK_H

#include "Hypersoft.h"

#ifndef HYPER_STACK_SYSTEM
	#define linkage extern
	typedef void * HyperStack;
#else
	#define linkage
#endif

/* PP_NARG is defined in Hypersoft.h */

#define HyperStackPush(stack, ...)                                             \
__HyperStackPush(stack, PP_NARG(__VA_ARGS__), __VA_ARGS__)
	
#define HyperStackUnshift(stack, ...)                                          \
__HyperStackUnshift(stack, PP_NARG(__VA_ARGS__), __VA_ARGS__)
//__HyperStackUnshift(stack, __VA_ARGS__, EOF)

linkage size_t __HyperStackPush(HyperStack stack, size_t arguments, ...);
linkage void * HyperStackPop(HyperStack stack);
linkage void * HyperStackShift(HyperStack stack);
linkage size_t __HyperStackUnshift(HyperStack stack, size_t arguments, ...);
linkage void * HyperStackPeek(HyperStack stack, size_t index);
linkage void * HyperStackPoke(HyperStack stack, size_t index, void * value);
linkage HyperStack HyperStackSlice(HyperStack stack, int64_t start, int64_t end);

linkage HyperStack hsCreateStack();
linkage void * hsFreeStack(HyperStack stack);

#endif /* HYPERSTACK_H */