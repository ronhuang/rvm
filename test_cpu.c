/*
Copyright (c) 2010, Ron Huang
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "fct.h"
#include "cpu.h"

FCTMF_FIXTURE_SUITE_BGN(cpu_suite) {

  FCT_SETUP_BGN() {
    rvm_cpu_reset();
  } FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
  } FCT_TEARDOWN_END();

  FCT_TEST_BGN(cpu_reset) {
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

  FCT_TEST_BGN(cpu_push) {
    Bit32u sp = reg_esp;
    Bit32u disp32;
    int ret;

    ret = rvm_cpu_push32u(0xFEEDBEEF);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(sp - 4, reg_esp);

    rvm_mem_load32u(reg_esp, &disp32);
    fct_chk_eq_int(disp32, 0xFEEDBEEF);
  } FCT_TEST_END();

  FCT_TEST_BGN(cpu_pop) {
    Bit32u sp = reg_esp;
    Bit32u disp32;
    int ret;

    rvm_mem_save32u(reg_esp, 0xFEEDBEEF);

    ret = rvm_cpu_pop32u(&disp32);
    fct_chk_eq_int(ret, SUCCESS);
    fct_chk_eq_int(sp + 4, reg_esp);
    fct_chk_eq_int(disp32, 0xFEEDBEEF);
  } FCT_TEST_END();

  FCT_TEST_BGN(cpu_flags_mask) {
    fct_chk_eq_int(FLAG_CF, 0x00000001);
    fct_chk_eq_int(FLAG_ZF, 0x00000040);
    fct_chk_eq_int(FLAG_SF, 0x00000080);
    fct_chk_eq_int(FLAG_OF, 0x00000800);
  } FCT_TEST_END();

  FCT_TEST_BGN(cpu_flags_set) {
    rvm_cpu_set_flag(FLAG_CF, 1);
    fct_chk_eq_int(CPU.flags & FLAG_CF, FLAG_CF);
    rvm_cpu_set_flag(FLAG_ZF, 1);
    fct_chk_eq_int(CPU.flags & FLAG_ZF, FLAG_ZF);
    rvm_cpu_set_flag(FLAG_SF, 1);
    fct_chk_eq_int(CPU.flags & FLAG_SF, FLAG_SF);
    rvm_cpu_set_flag(FLAG_OF, 1);
    fct_chk_eq_int(CPU.flags & FLAG_OF, FLAG_OF);

    rvm_cpu_set_flag(FLAG_CF, 0);
    fct_chk_eq_int(CPU.flags & FLAG_CF, 0x00000000);
    rvm_cpu_set_flag(FLAG_ZF, 0);
    fct_chk_eq_int(CPU.flags & FLAG_ZF, 0x00000000);
    rvm_cpu_set_flag(FLAG_SF, 0);
    fct_chk_eq_int(CPU.flags & FLAG_SF, 0x00000000);
    rvm_cpu_set_flag(FLAG_OF, 0);
    fct_chk_eq_int(CPU.flags & FLAG_OF, 0x00000000);
  } FCT_TEST_END();

  FCT_TEST_BGN(cpu_flags_get) {
    CPU.flags |= FLAG_CF;
    fct_chk(rvm_cpu_get_flag(FLAG_CF));
    CPU.flags |= FLAG_ZF;
    fct_chk(rvm_cpu_get_flag(FLAG_ZF));
    CPU.flags |= FLAG_SF;
    fct_chk(rvm_cpu_get_flag(FLAG_SF));
    CPU.flags |= FLAG_OF;
    fct_chk(rvm_cpu_get_flag(FLAG_OF));

    CPU.flags &= ~FLAG_CF;
    fct_chk(!rvm_cpu_get_flag(FLAG_CF));
    CPU.flags &= ~FLAG_ZF;
    fct_chk(!rvm_cpu_get_flag(FLAG_ZF));
    CPU.flags &= ~FLAG_SF;
    fct_chk(!rvm_cpu_get_flag(FLAG_SF));
    CPU.flags &= ~FLAG_OF;
    fct_chk(!rvm_cpu_get_flag(FLAG_OF));
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
