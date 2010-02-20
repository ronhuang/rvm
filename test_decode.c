#include "fct.h"
#include "decode.h"

static rvm_decode *decoder;

FCTMF_FIXTURE_SUITE_BGN(decode_suite) {

  FCT_SETUP_BGN() {
    decoder = rvm_decode_new();
    rvm_decode_set_source(decoder, "test/decode_basic");
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    rvm_decode_finalize(decoder);
    decoder = NULL;
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(test_next_instruction) {
    rvm_inst inst;
    int result;

    result = rvm_decode_next(decoder, &inst);
    fct_req(result == SUCCESS);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
