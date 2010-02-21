#include "fct.h"
#include "cpu.h"

FCTMF_FIXTURE_SUITE_BGN(cpu_suite) {

  FCT_SETUP_BGN() {
    rvm_cpu_reset();
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(test_reset) {
    Bit32u disp32;

    fct_chk_eq_int(reg_eax, 0);
    fct_chk_eq_int(reg_ecx, 0);
    fct_chk_eq_int(reg_edx, 0);
    fct_chk_eq_int(reg_ebx, 0);
    fct_chk_eq_int(reg_esp, 0);
    fct_chk_eq_int(reg_ebp, 0);
    fct_chk_eq_int(reg_esi, 0);
    fct_chk_eq_int(reg_edi, 0);

    fct_chk_eq_int(reg_eip, 0);
    fct_chk_eq_int(CPU.flags, 0);

    fct_chk_eq_int(reg_cs, 0);
    fct_chk_eq_int(reg_ss, 0);
    fct_chk_eq_int(reg_ds, 0);
    fct_chk_eq_int(reg_es, 0);
    fct_chk_eq_int(reg_fs, 0);
    fct_chk_eq_int(reg_gs, 0);
  } FCT_TEST_END();

  FCT_TEST_BGN(test_push) {
    Bit32u sp = reg_esp;
    Bit32u disp32;

    rvm_cpu_push32u(0xFEEDBEEF);
    fct_chk_eq_int(sp - 4, reg_esp);

    rvm_mem_load32u(reg_esp, &disp32);
    fct_chk_eq_int(disp32, 0xFEEDBEEF);
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
