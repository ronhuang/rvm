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
    fct_chk_eq_int(code.bs, -16);

    rvm_code_read32u(reader, &code.d);
    fct_chk_eq_int(code.d, 0xFEEDBEEF);
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
