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
