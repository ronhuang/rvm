#include "fct.h"
#include "type.h"

FCTMF_SUITE_BGN(type_suite) {

  FCT_TEST_BGN(test_sizeof) {
    fct_chk_eq_int(sizeof(Bit8u), 1);
    fct_chk_eq_int(sizeof(Bit8s), 1);
    fct_chk_eq_int(sizeof(Bit16u), 2);
    fct_chk_eq_int(sizeof(Bit16s), 2);
    fct_chk_eq_int(sizeof(Bit32u), 4);
    fct_chk_eq_int(sizeof(Bit32s), 4);
    fct_chk_eq_int(sizeof(Bit64u), 8);
    fct_chk_eq_int(sizeof(Bit64s), 8);
    fct_chk_eq_int(sizeof(Bitu), 4);
    fct_chk_eq_int(sizeof(Bits), 4);
  } FCT_TEST_END();

} FCTMF_SUITE_END();
