/*
Copyright (c) 2010, Ron Huang
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "fct.h"
#include "type.h"

FCTMF_SUITE_BGN(type_suite) {

  FCT_TEST_BGN(type_sizeof) {
    fct_chk_eq_int(sizeof(Bit8u), 1);
    fct_chk_eq_int(sizeof(Bit8s), 1);
    fct_chk_eq_int(sizeof(Bit16u), 2);
    fct_chk_eq_int(sizeof(Bit16s), 2);
    fct_chk_eq_int(sizeof(Bit32u), 4);
    fct_chk_eq_int(sizeof(Bit32s), 4);
    fct_chk_eq_int(sizeof(Bit64u), 8);
    fct_chk_eq_int(sizeof(Bit64s), 8);
    fct_chk_eq_int(sizeof(Bitu), 4);
    fct_chk_eq_int(sizeof(Bits), 4);
  } FCT_TEST_END();

  FCT_TEST_BGN(type_assign) {
    union {
      Bit32u d;
      Bit16u w[2];
      Bit8u b[4];
    } reg;

    reg.d = 0x12345678;
    fct_chk_eq_int(reg.b[0], 0x78);
    fct_chk_eq_int(reg.b[1], 0x56);
    fct_chk_eq_int(reg.b[2], 0x34);
    fct_chk_eq_int(reg.b[3], 0x12);

    reg.b[0] = 0xff;
    fct_chk_eq_int(reg.d, 0x123456ff);
  } FCT_TEST_END();

} FCTMF_SUITE_END();
