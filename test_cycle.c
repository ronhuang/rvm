#include "fct.h"
#include "cycle.h"

static rvm_cycle *runner;

FCTMF_FIXTURE_SUITE_BGN(cycle_suite) {

  FCT_SETUP_BGN() {
    runner = rvm_cycle_new();
    rvm_cycle_set_source(runner, "test/cycle_basic");
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    rvm_cycle_finalize(runner);
    runner = NULL;
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(test_step) {
    int result;

    result = rvm_cycle_step(runner);
    fct_req(result == SUCCESS);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
