/*

Tue Mar 11 10:09:45 CDT 2014

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

#define HYPERSOFT_C
#include "Hypersoft.h"
#undef HYPERSOFT_C

void * hsCopyMemory(void * dest, void * src, register size_t units) {
	register void **d = dest, ** s = src;
	register size_t copy = 0;
	while (copy < units) d[copy] = s[copy++];
	return dest;
}

void * hsCopyMemory8(void * dest, void * src, register size_t units) {
	register int8_t **d = dest, ** s = src;
	register size_t copy = 0;
	while (copy < units) d[copy] = s[copy++];
	return dest;
}

void * hsCopyMemory16(void * dest, void * src, register size_t units) {
	register int16_t **d = dest, ** s = src;
	register size_t copy = 0;
	while (copy < units) d[copy] = s[copy++];
	return dest;
}

void * hsCopyMemory32(void * dest, void * src, register size_t units) {
	register int32_t **d = dest, ** s = src;
	register size_t copy = 0;
	while (copy < units) d[copy] = s[copy++];
	return dest;
}

void * hsCopyMemory64(void * dest, void * src, register size_t units) {
	register int64_t **d = dest, ** s = src;
	register size_t copy = 0;
	while (copy < units) d[copy] = s[copy++];
	return dest;
}
