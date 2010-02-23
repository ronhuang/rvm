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
#include "mem.h"

FCTMF_FIXTURE_SUITE_BGN(mem_suite) {

  FCT_SETUP_BGN() {
    rvm_mem_reset();
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(mem_rw) {
    Bit32u disp32;
    int ret;

    /* *(0x00000000) = 0xFEEDBEEF */
    ret = rvm_mem_save32u(0x00000000, 0xFEEDBEEF);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_load32u(0x00000000, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(disp32, 0xFEEDBEEF);

    /* *(0x12345678) = 0x12345678 */
    ret = rvm_mem_save32u(0x12345678, 0x12345678);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_load32u(0x12345678, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(disp32, 0x12345678);

    /* *(0x87654321) = 0x87654321 */
    ret = rvm_mem_save32u(0x87654320, 0x87654321);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_load32u(0x87654320, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(disp32, 0x87654321);

    /* *(0xFFFFFFFF) = 0xCAFEBABE */
    ret = rvm_mem_save32u(0xFFFFFFFC, 0xCAFEBABE);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_load32u(0xFFFFFFFC, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(disp32, 0xCAFEBABE);
  } FCT_TEST_END();

  FCT_TEST_BGN(mem_reset) {
    Bit32u disp32;
    int ret;

    /* Write something */
    ret = rvm_mem_save32u(0x87654320, 0x87654321);
    fct_chk_eq_int(ret, SUCCESS);

    /* Execute */
    ret = rvm_mem_reset();
    fct_chk_eq_int(ret, SUCCESS);

    /* See if reset. */
    ret = rvm_mem_load32u(0x87654320, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(disp32, 0x00000000);
  } FCT_TEST_END();

  FCT_TEST_BGN(mem_alignment) {
    int ret;
    Bit32u disp32;

    ret = rvm_mem_save32u(0x87654320, 0x87654321);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_save32u(0x87654321, 0x87654321);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_save32u(0x87654322, 0x87654321);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_save32u(0x87654323, 0x87654321);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_save32u(0x87654324, 0x87654321);
    fct_chk_eq_int(ret, SUCCESS);

    ret = rvm_mem_load32u(0x87654320, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
    ret = rvm_mem_load32u(0x87654321, &disp32);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_load32u(0x87654322, &disp32);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_load32u(0x87654323, &disp32);
    fct_chk_eq_int(ret, FAIL);
    ret = rvm_mem_load32u(0x87654324, &disp32);
    fct_chk_eq_int(ret, SUCCESS);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
