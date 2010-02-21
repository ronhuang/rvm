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

  FCT_TEST_BGN(cycle_step_mnemonic) {
    int result;
    rvm_inst inst;
    int i;

    /* Check first instruction. */
    result = rvm_cycle_step(runner);
    fct_req(result == SUCCESS);

    rvm_cycle_get_executed_instruction(runner, &inst);
    fct_chk_eq_str(inst.mnemonic, "lea");

    /* Skip the middle instructions. */
    for (i = 1; i < 9; i++) {
      result = rvm_cycle_step(runner);
      fct_req(result == SUCCESS);
    }

    /* Check last instruction */
    result = rvm_cycle_step(runner);
    fct_req(result == SUCCESS);

    rvm_cycle_get_executed_instruction(runner, &inst);
    fct_chk_eq_str(inst.mnemonic, "pop");
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
