#include "fct.h"
#include "cpu.h"
#include "code.h"
#include "cycle.h"

static rvm_cycle *runner;
static rvm_code *reader;

FCTMF_FIXTURE_SUITE_BGN(cycle_suite) {

  FCT_SETUP_BGN() {
    /* Setup environment. */
    rvm_cpu_reset();
    rvm_mem_reset();
    reg_esp = 0xFEEDBEEF;

    reader = rvm_code_new();
    runner = rvm_cycle_new();
    rvm_cycle_set_code(runner, reader);
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    rvm_cycle_finalize(runner);
    runner = NULL;
    rvm_code_finalize(reader);
    reader = NULL;
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(cycle_inst_lea) {
    int result;

    /* Set source. */
    /* lea ecx,[esp+4] */
    rvm_code_set_string_source(reader, "8d 4c 24 04");

    /* Prerequisite. */
    fct_chk_eq_int(reg_ecx, 0);

    /* Execute */
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_ecx, reg_esp + 4);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_and) {
    int result;
    Bit32u value = 0x12345678;

    /* Set source. */
    /* and esp,0xfffffff0 */
    rvm_code_set_string_source(reader, "83 e4 f0");

    /* Prerequisite. */
    fct_chk_neq_int(value, value & 0xfffffff0);

    /* Execute */
    reg_esp = value;
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_esp, value & 0xfffffff0);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_step_mnemonic) {
    int result;
    rvm_inst inst;
    int i;

    /* Set source. */
    rvm_code_set_file_source(reader, "sample/cycle_basic");

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
