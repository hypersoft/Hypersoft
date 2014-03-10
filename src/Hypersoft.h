/*

Sun Mar  2 05:13:57 CST 2014

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

#ifndef HYPERSOFT_H
#define HYPERSOFT_H

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "utfx.h"

#define hsSubProc(...)                                                         \
{ \
	__VA_ARGS_; \
}

#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)

#define PP_ARG_N( \
_256, _255, _254, _253, _252, _251, _250, _249, _248, _247, \
_246, _245, _244, _243, _242, _241, _240, _239, _238, _237, \
_236, _235, _234, _233, _232, _231, _230, _229, _228, _227, \
_226, _225, _224, _223, _222, _221, _220, _219, _218, _217, \
_216, _215, _214, _213, _212, _211, _210, _209, _208, _207, \
_206, _205, _204, _203, _202, _201, _200, _199, _198, _197, \
_196, _195, _194, _193, _192, _191, _190, _189, _188, _187, \
_186, _185, _184, _183, _182, _181, _180, _179, _178, _177, \
_176, _175, _174, _173, _172, _171, _170, _169, _168, _167, \
_166, _165, _164, _163, _162, _161, _160, _159, _158, _157, \
_156, _155, _154, _153, _152, _151, _150, _149, _148, _147, \
_146, _145, _144, _143, _142, _141, _140, _139, _138, _137, \
_136, _135, _134, _133, _132, _131, _130, _129, _128, _127, \
_126, _125, _124, _123, _122, _121, _120, _119, _118, _117, \
_116, _115, _114, _113, _112, _111, _110, _109, _108, _107, \
_106, _105, _104, _103, _102, _101, _100, _99, _98, _97, _96, \
_95, _94, _93, _92, _91, _90, _89, _88, _87, _86, _85, _84, \
_83, _82, _81, _80, _79, _78, _77, _76, _75, _74, _73, _72, \
_71, _70, _69, _68, _67, _66, _65, _64, _63, _62, _61, _60, \
_59, _58, _57, _56, _55, _54, _53, _52, _51, _50, _49, _48, \
_47, _46, _45, _44, _43, _42, _41, _40, _39, _38, _37, _36, \
_35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, \
_23, _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, \
_11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N

#define PP_RSEQ_N() \
256, 255, 254, 253, 252, 251, 250, 249, 248, 247, 246, 245, \
244, 243, 242, 241, 240, 239, 238, 237, 236, 235, 234, 233, \
232, 231, 230, 229, 228, 227, 226, 225, 224, 223, 222, 221, \
220, 219, 218, 217, 216, 215, 214, 213, 212, 211, 210, 209, \
208, 207, 206, 205, 204, 203, 202, 201, 200, 199, 198, 197, \
196, 195, 194, 193, 192, 191, 190, 189, 188, 187, 186, 185, \
184, 183, 182, 181, 180, 179, 178, 177, 176, 175, 174, 173, \
172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, \
160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, \
148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, \
136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, \
124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, \
112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, \
100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86,\
 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71,\
 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56,\
 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41,\
 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,\
 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11,\
 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0


#define hsBit(n) (1LL << ((n)-1))
#define hsIsBit(test, bit) (test & hsBit(bit))


#endif /* HYPERSOFT_H */