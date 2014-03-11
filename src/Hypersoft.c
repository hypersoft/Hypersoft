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

size_t __hsFree(size_t arguments, ...) {
	register size_t index = 0;
	va_list ap; va_start(ap, arguments);
	while (index++ < arguments) free(va_arg(ap, void *));
	va_end(ap);
}

void * hsScanMemory(void * loc, size_t value, size_t start, size_t *end)
{

	register size_t e;

	if (! loc ) return NULL;
	else if (! end ) return loc;
	else if (start > *end) return NULL;
	else if (! (e = *end)) return NULL;

	register size_t *l = loc;
	register size_t scan = start;
	while (scan < e) if (l[scan++] == value) {
		*end = --scan;
		return l + scan;
	}
	return (void*)(*end = 0);
}

void * hsScanMemory8(void * loc, int8_t value, size_t start, size_t *end)
{

	register size_t e;

	if (! loc ) return NULL;
	else if (! end ) return loc;
	else if (start > *end) return NULL;
	else if (! (e = *end)) return NULL;

	register int8_t *l = loc;
	register size_t scan = start;
	while (scan < e) if (l[scan++] == value) {
		*end = --scan;
		return l + scan;
	}
	return (void*)(*end = 0);
}

void * hsScanMemory16(void * loc, int16_t value, size_t start, size_t *end)
{

	register size_t e;

	if (! loc ) return NULL;
	else if (! end ) return loc;
	else if (start > *end) return NULL;
	else if (! (e = *end)) return NULL;

	register int16_t *l = loc;
	register size_t scan = start;
	while (scan < e) if (l[scan++] == value) {
		*end = --scan;
		return l + scan;
	}
	return (void*)(*end = 0);
}

void * hsScanMemory32(void * loc, int32_t value, size_t start, size_t *end)
{

	register size_t e;

	if (! loc ) return NULL;
	else if (! end ) return loc;
	else if (start > *end) return NULL;
	else if (! (e = *end)) return NULL;

	register int32_t *l = loc;
	register size_t scan = start;
	while (scan < e) if (l[scan++] == value) {
		*end = --scan;
		return l + scan;
	}
	return (void*)(*end = 0);
}

void * hsScanMemory64(void * loc, int64_t value, size_t start, size_t *end)
{

	register size_t e;

	if (! loc ) return NULL;
	else if (! end ) return loc;
	else if (start > *end) return NULL;
	else if (! (e = *end)) return NULL;

	register int64_t *l = loc;
	register size_t scan = start;
	while (scan < e) if (l[scan++] == value) {
		*end = --scan;
		return l + scan;
	}
	return (void*)(*end = 0);
}

void * hsSetMemory(void * loc, register size_t value, register size_t units) {
	register size_t *l = loc;
	register size_t set = 0;
	while (set < units) l[set++] = value;
	return loc;
}

void * hsSetMemory8(void * loc, register int8_t value, register size_t units) {
	register int8_t *l = loc;
	register size_t set = 0;
	while (set < units) l[set++] = value;
	return loc;
}

void * hsSetMemory16(void * loc, register int16_t value, register size_t units)
{
	register int16_t *l = loc;
	register size_t set = 0;
	while (set < units) l[set++] = value;
	return loc;
}

void * hsSetMemory32(void * loc, register int32_t value, register size_t units)
{
	register int32_t *l = loc;
	register size_t set = 0;
	while (set < units) l[set++] = value;
	return loc;
}

void * hsSetMemory64(void * loc, register int64_t value, register size_t units)
{
	register int64_t *l = loc;
	register size_t set = 0;
	while (set < units) l[set++] = value;
	return loc;
}

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
