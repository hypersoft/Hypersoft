/*

Fri Feb 28 07:38:46 CST 2014

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

#ifndef HYPERVARIANT_H
#define HYPERVARIANT_H

#include "Hypersoft.h"

#ifndef HYPER_VARIANT_AUTO_PADDING
	#if __WORDSIZE == 64
		#define HYPER_VARIANT_AUTO_PADDING 8
	#else
		#define HYPER_VARIANT_AUTO_PADDING 4
	#endif
#endif

typedef enum iHyperVariantError {
	HSV_ERROR_NONE,
	HSV_ERROR_VARIANT_IS_NULL,
	HSV_ERROR_REFERENCE_IS_NULL,
	HSV_ERROR_CALL_BACK_IS_NULL,
	HSV_ERROR_BLOCK_TYPE_REQUIRED,
	HSV_ERROR_BLOCK_SIZE_REQUIRED,
	HSV_ERROR_BLOCK_UNITS_REQUIRED,
	HSV_ERROR_TYPE_SIZE_REQUIRED,
} HyperVariantError;

typedef enum iHyperSoftVariant {
	HSV1 =      hsBit(1)     ,
	HSV2   =    hsBit(2)   ,
	HSV4     =  hsBit(3) ,
	HSV8      = hsBit(4),
	HSV_FLOAT = hsBit(5), HSVF = HSV_FLOAT,
	HSV_BLOCK = hsBit(6), HSVB = HSV_BLOCK,
	HSV_ZERO  = hsBit(7), HSVZ = HSV_ZERO
	/*        It's a full house          */
} HyperSoftVariant;

/* I like the way these look standing out where applicable... tt */
#define HSV1 HSV1
#define HSV2 HSV2
#define HSV4 HSV4
#define HSV8 HSV8
#define HSVF HSVF
#define HSVB HSVB
#define HSVZ HSVZ

typedef enum iHyperSoftSelect {
	HSSA, HSS_ASCEND  = HSSA,
	HSSD, HSS_DESCEND = HSSD
} HyperSoftSelect;

#define HSSA HSSA
#define HSSD HSSD

typedef enum iHyperSoftShift {
	HSSL, HSS_LEFT  = HSSL,
	HSSR, HSS_RIGHT = HSSR
} HyperSoftShift;

#define HSSL HSSL
#define HSSR HSSR

#define char8_t char

typedef struct iHyperVariant {
	uint8_t permission;
	uint8_t state, reserve; 
	uint8_t type;
	size_t units;
	uint8_t data[];
} iHyperVariant;

typedef iHyperVariant * HyperVariant;

/* make sure length is an lvalue! */
#define hsRequiresPadding(length) (length % HYPER_VARIANT_AUTO_PADDING)

/* make sure length is an lvalue! */
#define hsLogicalPadding(length)  \
	(HYPER_VARIANT_AUTO_PADDING - (length % HYPER_VARIANT_AUTO_PADDING))

/* pointer to ... */
#define ptrto(t, p)  (t *)(p)

/* value of ... */
#define valof(t, p) *(t *)(p)

/* cast-a-pointer */
#define dblval(p) valof(double, p)
#define dblptr(p) ptrto(double, p)
#define fltval(p) valof(float, p)
#define fltptr(p) ptrto(float, p)
#define lenval(p) valof(size_t, p)
#define lenptr(p) ptrto(size_t, p)
#define ptrval(p) valof(void*, p)
#define ptrptr(p) ptrto(void*, p)
#define int8val(p) valof(uint8_t, p)
#define int8ptr(p) ptrto(uint8_t, p)
#define int16val(p) valof(uint16_t, p)
#define int16ptr(p) ptrto(uint16_t, p)
#define int32val(p) valof(uint32_t, p)
#define int32ptr(p) ptrto(uint32_t, p)
#define int64val(p) valof(uint64_t, p)
#define int64ptr(p) ptrto(uint64_t, p)
#define utf8val(p) valof(char8_t, p)
#define utf8ptr(p) ptrto(char8_t, p)
#define utf16val(p) valof(char16_t, p)
#define utf16ptr(p) ptrto(char16_t, p)
#define utf32val(p) valof(char32_t, p)
#define utf32ptr(p) ptrto(char32_t, p)

/* define-a-blok */
#define blkref(t, n, p) t * n = (t*) p
/* block scan forward*/
#define iblkval(t, p, i) valof(t, (((i)*sizeof(t))+(p)))
/* block scan reverse */
#define iblkrev(t, p, i) valof(t, ((p)-((i)*sizeof(t))))

/* create-a-var */
#define dblvar(dV) hsCreateVariant(HSVF|8, dV)
#define fltvar(dV) hsCreateVariant(HSVF|4, (float*)dV)
#define lenvar(nV) hsCreateVariant(sizeof(size_t), nV)
#define ptrvar(pV) hsCreateVariant(sizeof(void*), pV)
#define int8var(cV) hsCreateVariant(1, cV)
#define int16var(sV) hsCreateVariant(2, sV)
#define int32var(lV) hsCreateVariant(4, lV)
#define int64var(llV) hsCreateVariant(8, llV)
#define utf8var(pV) hsCreateVariant(HSVB|HSVZ|1, 0, pV)
#define utf32var(pV) hsCreateVariant(HSVB|HSVZ|4, 0, pV)
#define blkvar(type, count, pointer) \
	hsCreateVariant(HSVB|sizeof(type), count, pointer)

#ifndef HYPER_VARIANT_SYSTEM
	#define linkage extern
#else
	#define linkage inline
#endif

linkage size_t hsVariantImpact(register HyperVariant var);
linkage size_t hsVariantSize(register HyperVariant var);
linkage size_t hsVariantLength(register HyperVariant var);

linkage HyperVariant hsVariantSlice
(HyperVariant var,
	long long start,
		long long end);

linkage void hsFreeVariant(HyperVariant * var);
linkage void hsEraseVariant(HyperVariant var, size_t from, size_t to);
linkage HyperVariant hsCreateVariant(size_t type, ...);
linkage size_t hsReallocVariant(HyperVariant * var, size_t units);

typedef void * (*VariantSelector)
(HyperSoftSelect mode,
	HyperSoftVariant type,
		void *primary,
			void *secondary,
				void *private);

typedef int32_t (*VariantIterator)
(HyperSoftVariant type,
	void *value,
		void *private );

#define hsVariantEnumForward hsVariantForEach

linkage void hsVariantSort
(HyperVariant var,
	HyperSoftSelect mode,
		VariantSelector select,
			void *private     );

linkage void hsVariantForEach
(HyperVariant var,
	VariantIterator forEach,
		void *private      );

linkage void hsVariantEnumReverse
(HyperVariant var,
	VariantIterator forEach,
		void *private      );

#undef linkage

#endif 