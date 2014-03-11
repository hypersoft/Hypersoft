/*

Fri Feb 28 07:38:43 CST 2014

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

#define HYPER_VARIANT_SYSTEM

#include "HyperVariant.h"

#define hsIfVariantIsNull(variant, ...)                                        \
if (!variant) { errno = HSV_ERROR_VARIANT_IS_NULL; __VA_ARGS__; }

#define hsIfReferenceIsNull(reference, ...)                                    \
if (!reference) { errno = HSV_ERROR_REFERENCE_IS_NULL; __VA_ARGS__; }

#define hsIfCallBackIsNull(callBack, ...)                                      \
if (!callBack) { errno = HSV_ERROR_CALL_BACK_IS_NULL; __VA_ARGS__; }

#define hsReturnIfBlockTypeRequired(variant, ...)                              \
if (!variant & HSVB) {                                                         \
	errno = HSV_ERROR_BLOCK_TYPE_REQUIRED; return __VA_ARGS__;                 \
}

#define hsBlockUnitsAreRequired(...)                                           \
{errno = HSV_ERROR_BLOCK_UNITS_REQUIRED; __VA_ARGS__;}

#define hsTypeSizeRequired(...)                                                \
{errno = HSV_ERROR_TYPE_SIZE_REQUIRED; __VA_ARGS__;}


size_t hsVariantImpact(register HyperVariant var) {

	hsIfVariantIsNull(var, return 0);

	size_t terminator = (var->type & HSVZ) ? 1 : 0;
	register size_t bytes =
		(var->type & (1|2|4|8)) * (var->units + terminator + var->reserve);
	register size_t paddedBytes;
	if (bytes < sizeof(double)) paddedBytes = sizeof(double);
	else  paddedBytes = hsRequiresPadding(bytes) ?
		bytes + hsLogicalPadding(bytes)
			: bytes;
	return paddedBytes + sizeof(iHyperVariant);

}

size_t hsVariantSize(register HyperVariant var) {

	hsIfVariantIsNull(var, return 0);

	return (var->type & (1|2|4|8));
}

#define hsVariantSize(var) (var) ? var->type & (1|2|4|8) : 0

size_t hsVariantLength(register HyperVariant var) {

	hsIfVariantIsNull(var, return 0);

	register uint8_t type = var->type, units = var->units;
	return ((type & (1|2|4|8)) * units);
}

HyperVariant hsVariantSlice(HyperVariant var, int64_t start, int64_t end) {

	hsIfVariantIsNull(var, NULL) else
		hsReturnIfBlockTypeRequired(var, NULL);

	/* on 64-bit platforms, negative indices are only half width capable...  */
	/* this is a major setback.. there should be a standard integer > size_t */
	/* for every platform, otherwise, you can't correctly reference memory.  */

	{
		register size_t max = var->units;
		if (start < 0) start = max + start;
		if (start < 0) return NULL; /* we tried... */
		else if (start >= max) return NULL;

		if (end < 0) end = max + start;
		if (end < 0) return NULL; /* we tried ... */
		else if (end > max || ! end) end = max;
	}

	if (start > end) return NULL;

	size_t units = end - start;

	if (! units) units++;
	return hsCreateVariant(
		var->type, units, var->data + ((var->type & (1|2|4|8)) * start)
	);

}

void hsVariantSort
(
	HyperVariant var,
	HyperSoftSelect mode,
	VariantSelector select,
	void *private
) {

	hsIfVariantIsNull(var, return) else
		hsIfCallBackIsNull(select, return);

	uint8_t type = var->type;

	if (type & 1) {
		uint8_t * value, * alternative; void * selection;
		register size_t secondary;
		size_t primary, units = var->units;
		register uint8_t * block = int8ptr(var->data);
		for (primary = 0; primary < units; primary++) {
			for (secondary = primary + 1; secondary < units; secondary++) {
				value = &block[primary],
				alternative = &block[secondary],
				selection = select(mode, type, value, alternative, private);
				if (!selection) return; else
				if (selection == alternative) {
					uint8_t swap = *alternative;
						block[secondary] = *value,
							block[primary] = swap;
				}
			}
		}
		return;
	} else
	if (type & 2) {
		uint16_t *value, *alternative; void *selection;
		register size_t secondary;
		size_t primary, units = var->units;
		register uint16_t * block = int16ptr(var->data);
		for (primary = 0; primary < units; primary++) {
			for (secondary = primary + 1; secondary < units; secondary++) {
				value = &block[primary],
				alternative = &block[secondary],
				selection = select(mode, type, value, alternative, private);
				if (!selection) return; else
				if (selection == alternative) {
					int16_t swap = *alternative;
						block[secondary] = *value,
							block[primary] = swap;
				}
			}
		}
		return;
	} else
	if (type & 4) {
		uint32_t *value, *alternative; void * selection;
		register size_t secondary;
		size_t primary, units = var->units;
		register size_t * block = lenptr(var->data);
		for (primary = 0; primary < units; primary++) {
			for (secondary = primary + 1; secondary < units; secondary++) {
				value = &block[primary],
				alternative = &block[secondary],
				selection = select(mode, type, value, alternative, private);
				if (!selection) return; else
				if (selection == alternative) {
					int32_t swap = *alternative;
						block[secondary] = *value,
							block[primary] = swap;
				}
			}
		}
		return;
	} else {
		uint64_t *value, *alternative; void * selection;
		register size_t secondary;
		size_t primary, units = var->units;
		register uint64_t * block = int64ptr(var->data);
		for (primary = 0; primary < units; primary++) {
			for (secondary = primary + 1; secondary < units; secondary++) {
				value = &block[primary],
				alternative = &block[secondary],
				selection = select(mode, type, value, alternative, private);
				if (!selection) return; else
				if (selection == alternative) {
					int32_t swap = *alternative;
						block[secondary] = *value,
							block[primary] = swap;
				}
			}
		}
		return;
	}

}

void hsVariantForEach(HyperVariant var, VariantIterator forEach, void *p) {

	hsIfVariantIsNull(var, return) else
		hsIfCallBackIsNull(forEach, return);
	uint8_t type = var->type;
	register size_t unit = 0, max = var->units;
	if (type & 1) {
		register blkref(uint8_t, block, var->data);
		while (unit < max)
			if (!forEach(type, &block[unit++], p)) break;
	} else
	if (type & 2) {
		register blkref(uint16_t, block, var->data);
		while (unit < max)
			if (!forEach(type, &block[unit++], p)) break;
	} else
	if (type & 4) {
		register blkref(uint32_t, block, var->data);
		while (unit < max)
			if (!forEach(type, &block[unit++], p)) break;
	} else {
		register blkref(uint64_t, block, var->data);
		while (unit < max)
			if (!forEach(type, &block[unit++], p)) break;
	}
}

void hsVariantEnumReverse(HyperVariant var, VariantIterator forEach, void *p) {

	hsIfVariantIsNull(var, return) else
		hsIfCallBackIsNull(forEach, return);

	uint8_t type = var->type;
	register size_t count = var->units;
	if (type & 1) {
		register uint8_t * block = int8ptr(var->data);
		while (count)
			if (!forEach(type, &block[--count], p)) break;
	} else
	if (type & 2) {
		register uint16_t * block = int16ptr(var->data);
		while (count)
			if (!forEach(type, &block[--count], p)) break;
	} else
	if (type & 4) {
		register size_t * block = lenptr(var->data);
		while (count)
			if (!forEach(type, &block[--count], p)) break;
	} else {
		register uint64_t * block = int64ptr(var->data);
		while (count)
			if (!forEach(type, &block[--count], p)) break;
	}
}

HyperVariant hsCreateVariant(size_t type, ...) {

	va_list ap; va_start(ap, type);

	register size_t bytes = (type & (1|2|4|8)), count = 1;
	size_t zeroTerminate = (type & HSV_ZERO) ? 1 : 0;

	if (type & HSV_BLOCK) {
		count = va_arg(ap, size_t);
		if (zeroTerminate && !count) {
			if (type & 1) count = strlen8(va_arg(ap, char8_t*)); else
			if (type & 2) count = strlen16(va_arg(ap, char16_t*)); else
			if (type & 4) count = strlen32(va_arg(ap, char32_t*)); else
			hsBlockUnitsAreRequired(return 0)
			va_end(ap); va_start(ap, type); va_arg(ap, size_t);
		}
	}

	bytes *= (count + zeroTerminate);
	size_t paddedBytes = 0;
	if (bytes < sizeof(double)) paddedBytes = sizeof(double);
	else paddedBytes = hsRequiresPadding(bytes)?
		bytes + hsLogicalPadding(bytes)
	: bytes;
	HyperVariant result = malloc(sizeof(iHyperVariant) + paddedBytes);
	int32val(result) = 0,
		result->type = type,
			result->units = count;
	register blkref(char, block, result->data);
	{ register size_t zeroIndex = bytes;
		while (zeroIndex < paddedBytes) block[zeroIndex++] = 0; }
	if (type & HSV_FLOAT) {
		if (bytes == 4) fltval(block) = *(float*)va_arg(ap, float *);
		else dblval(block) = va_arg(ap, double);
	} else {
		if (type & HSV_BLOCK) memcpy(result->data, va_arg(ap, void*), bytes);
		else if (bytes == 1) int8val(block) = (char)va_arg(ap, int32_t);
		else if (bytes == 2) int16val(block) = (short)va_arg(ap, int32_t);
		else if (bytes == 4) int32val(block) = va_arg(ap, int32_t);
		else if (bytes == 8) int64val(block) = va_arg(ap, uint64_t);
		else hsTypeSizeRequired(return NULL);
	}

	va_end(ap);

	return result;

}

size_t hsReallocVariant(HyperVariant * var, size_t units) {

	hsIfReferenceIsNull(var, return 0) else
		hsIfVariantIsNull(*var, return 0);

	size_t paddedBytes = 0;

	HyperVariant source = *var;
	uint8_t type = source->type;
	register size_t bytes = (type & (1|2|4|8)) * units +
		(type & HSV_ZERO) ? 1 : 0;

	if (type & HSV_BLOCK) {
		if (units == 0) {
			if (type & 1) units = strlen8(utf8ptr(source->data)); else
			if (type & 2) units = strlen16(utf16ptr(source->data)); else
			if (type & 4) units = strlen32(utf32ptr(source->data)); else
			if (type & 8) hsBlockUnitsAreRequired(return 0);
		}
	}
	if (bytes < sizeof(double)) paddedBytes = sizeof(double);
	else  paddedBytes = hsRequiresPadding(bytes)
			? bytes + hsLogicalPadding(bytes)
				: bytes;
	HyperVariant result = malloc(sizeof(iHyperVariant) + paddedBytes);
	if (!result) return 0; else int32val(result) = 0;
	if (units > source->units) bytes = hsVariantLength(source),
		result->reserve = units - source->units;
	register blkref(uint8_t, block, result->data);
	while (bytes < paddedBytes) block[bytes++] = 0;
	result->type = type,
		result->units = units,
			memcpy(result->data, source->data, bytes);
	hsFreeVariant(var);
	*var = result;
	return units;
}

void hsFreeVariant(register HyperVariant * var) {

	hsIfReferenceIsNull(var, return) else
		hsIfVariantIsNull(*var, return);

	if (! var || ! *var) return;
	free(*var);
	*var = NULL;
	return;
}

void hsEraseVariant(HyperVariant var, register size_t from, size_t to) {

	hsIfVariantIsNull(var, return);

	uint8_t type = var->type;
	register size_t length = var->units;
	if (to && to <= length) length = to;
	if (type & 1) {
		register uint8_t * block = int8ptr(var->data);
		while (from < length) block[from++] = 0;
		return;
	} else
	if (type & 2) {
		register uint16_t * block = int16ptr(var->data);
		while (from < length) block[from++] = 0;
		return;
	} else
	if (type & 4) {
		register size_t * block = lenptr(var->data);
		while (from < length) block[from++] = 0;
		return;
	} else {
		register uint64_t * block = int64ptr(var->data);
		while (from < length) block[from++] = 0;
		return;
	}
	return;
}
