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

  FCT_TEST_BGN(test_single_line) {
    Bit8u code = 0;
    int i;

    /* Otherwise no point in testing further! */
    fct_req(reader != NULL);

    rvm_code_set_source(reader, "test/code_single_line");

    /* Test first 5 bytes. */
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x8d);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x4c);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x24);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x04);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x83);

    /* Skip to last 5 */
    for (i = 5; i < 20; i++) {
      rvm_code_read(reader);
    }

    /* Test last 5 bytes. */
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x7c);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x24);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x04);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x81);
    code = rvm_code_read(reader);
    fct_chk_eq_int(code, 0x5d);
  } FCT_TEST_END();

  FCT_TEST_BGN(test_multiple_lines) {
  } FCT_TEST_END();

  FCT_TEST_BGN(test_multiple_lines_with_comment) {
  } FCT_TEST_END();

  FCT_TEST_BGN(test_multiple_lines_with_long_comment) {
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
