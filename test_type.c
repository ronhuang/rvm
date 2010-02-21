#include "fct.h"
#include "type.h"

FCTMF_SUITE_BGN(type_suite) {

  FCT_TEST_BGN(type_sizeof) {
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

  FCT_TEST_BGN(type_assign) {
    union {
      Bit32u d;
      Bit16u w[2];
      Bit8u b[4];
    } reg;

    reg.d = 0x12345678;
    fct_chk_eq_int(reg.b[0], 0x78);
    fct_chk_eq_int(reg.b[1], 0x56);
    fct_chk_eq_int(reg.b[2], 0x34);
    fct_chk_eq_int(reg.b[3], 0x12);

    reg.b[0] = 0xff;
    fct_chk_eq_int(reg.d, 0x123456ff);
  } FCT_TEST_END();

} FCTMF_SUITE_END();
