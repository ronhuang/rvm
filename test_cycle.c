#include "fct.h"
#include "cycle.h"
#include "code.h"

static rvm_cycle *runner;
static rvm_code *reader;

FCTMF_FIXTURE_SUITE_BGN(cycle_suite) {

  FCT_SETUP_BGN() {
    reader = rvm_code_new();
    rvm_code_set_source(reader, "test/cycle_basic");

    runner = rvm_cycle_new();
    rvm_cycle_set_code(runner, reader);
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    rvm_cycle_finalize(runner);
    runner = NULL;

    rvm_code_finalize(reader);
    reader = NULL;
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(test_step) {
    int result;

    result = rvm_cycle_step(runner);
    fct_req(result == SUCCESS);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
