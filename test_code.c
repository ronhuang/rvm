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
#include "code.h"

static rvm_code *reader;

FCTMF_FIXTURE_SUITE_BGN(code_suite) {

  FCT_SETUP_BGN() {
    reader = rvm_code_new();
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    rvm_code_finalize(reader);
    reader = NULL;
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(code_single_line) {
    Bit8u code = 0;
    int i;
    int ret;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    ret = rvm_code_set_file_source(reader, "sample/code_single_line");
    fct_req(ret == SUCCESS);

    /* Test first 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x8d);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x4c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x83);

    /* Skip to last 5 */
    for (i = 5; i < 20; i++) {
      rvm_code_read(reader, &code);
    }

    /* Test last 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x7c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x81);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x5d);
  } FCT_TEST_END();

  FCT_TEST_BGN(code_multiple_lines) {
    Bit8u code = 0;
    int i;
    int ret;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    ret = rvm_code_set_file_source(reader, "sample/code_multiple_lines");
    fct_req(ret == SUCCESS);

    /* Test first 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x8d);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x4c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x83);

    /* Skip to last 5 */
    for (i = 5; i < 220; i++) {
      rvm_code_read(reader, &code);
    }

    /* Test last 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x7c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x81);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x5d);
  } FCT_TEST_END();

  FCT_TEST_BGN(code_multiple_lines_with_comment) {
    Bit8u code = 0;
    int i;
    int ret;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    ret = rvm_code_set_file_source(reader, "sample/code_multiple_lines_with_comment");
    fct_req(ret == SUCCESS);

    /* Test first 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x8d);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x4c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x83);

    /* Skip to last 5 */
    for (i = 5; i < 20; i++) {
      rvm_code_read(reader, &code);
    }

    /* Test last 5 bytes. */
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x7c);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x24);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x04);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x81);
    rvm_code_read(reader, &code);
    fct_chk_eq_int(code, 0x5d);
  } FCT_TEST_END();

  FCT_TEST_BGN(code_read_multi_bytes) {
    union {
      Bit8u b;
      Bit8s bs;
      Bit16u w;
      Bit16s ws;
      Bit32u d;
      Bit32s ds;
    } code;
    int ret;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    ret = rvm_code_set_file_source(reader, "sample/code_multi_bytes");
    fct_req(ret == SUCCESS);

    rvm_code_read8s(reader, &code.bs);
    fct_chk_eq_int(code.bs, -119);

    rvm_code_read32u(reader, &code.d);
    fct_chk_eq_int(code.d, 0x04ec83e5);
  } FCT_TEST_END();

  FCT_TEST_BGN(code_read_buffer) {
    int ret;
    Bit8u code;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    ret = rvm_code_set_string_source(reader,
                                     "50                       # push eax\n"
                                     "c1 f8 02                 # sar eax,0x02\n"
                                     );
    fct_chk_eq_int(ret, SUCCESS);

    rvm_code_read8u(reader, &code);
    fct_chk_eq_int(code, 0x50);
    rvm_code_read8u(reader, &code);
    fct_chk_eq_int(code, 0xc1);
    rvm_code_read8u(reader, &code);
    fct_chk_eq_int(code, 0xf8);
    rvm_code_read8u(reader, &code);
    fct_chk_eq_int(code, 0x02);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
