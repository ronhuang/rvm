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
#include "code.h"
#include "cycle.h"

static rvm_cycle *runner;
static rvm_code *reader;

FCTMF_FIXTURE_SUITE_BGN(cycle_suite) {

  FCT_SETUP_BGN() {
    /* Setup environment. */
    rvm_cpu_reset();
    rvm_mem_reset();
    reg_esp = 0xFEEDBEEC;

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

  FCT_TEST_BGN(cycle_inst_push) {
    int result;
    Bit32u value = 0x12345678;
    Bit32u disp32;
    Bit32u new_esp;

    /* Prerequisite */
    new_esp = reg_esp - 4;
    rvm_mem_load32u(new_esp, &disp32);
    fct_chk_neq_int(disp32, value);

    /* Execute: push eax */
    reg_eax = value;
    rvm_code_set_string_source(reader, "50");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    rvm_mem_load32u(reg_esp, &disp32);
    fct_chk_eq_int(disp32, value);
    fct_chk_eq_int(reg_esp, new_esp);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_sar) {
    /* Negative */
    /* Set source */
    /* sar eax,0x02 */
    rvm_code_set_string_source(reader, "c1 f8 02");

    /* Execute */
    reg_eax = 0xffff0000;
    rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(reg_eax, 0xffffc000);


    /* Positive */
    /* Set source */
    /* sar eax,0x02 */
    rvm_code_set_string_source(reader, "c1 f8 02");

    /* Execute */
    reg_eax = 0x0ffff000;
    rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(reg_eax, 0x03fffc00);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_xor) {
    int result;
    Bit32u value = 0x66;
    Bit32u disp32;

    /* Set source */
    /* xor al,0x2e */
    rvm_code_set_string_source(reader, "34 2e");

    /* Prerequisite */
    fct_chk_neq_int(value, value ^ 0x2e);

    /* Execute */
    reg_al = value;
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_al, value ^ 0x2e);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_mov) {
    int result;

    /* Prerequisite */
    reg_esp = 0xCAFEBABE;
    fct_chk_neq_int(reg_esp, reg_ebp);

    /* Execute: mov ebp,esp */
    rvm_code_set_string_source(reader, "89 e5");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_esp, reg_ebp);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_inc) {
    int result;

    /* Prerequisite */
    reg_ebp = 0xCAFEBABE;

    /* Execute: inc ebp */
    rvm_code_set_string_source(reader, "45");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_ebp, 0xCAFEBABE + 1);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_sub) {
    int result;

    /* Prerequisite */
    reg_esp = 0xCAFEBABE;

    /* Execute: sub esp,0x04 */
    rvm_code_set_string_source(reader, "83 ec 04");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_esp, 0xCAFEBABE - 0x04);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_cmp) {
    int result;

    /* Prerequisite */
    fct_chk(!rvm_cpu_get_flag(FLAG_CF)); fct_chk(!rvm_cpu_get_flag(FLAG_ZF));
    fct_chk(!rvm_cpu_get_flag(FLAG_SF)); fct_chk(!rvm_cpu_get_flag(FLAG_OF));

    /* Execute: cmp [esp+4],0x81 */
    rvm_mem_save32u(reg_esp + 4, 0x82);
    rvm_code_set_string_source(reader, "80 7c 24 04 81");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk(!rvm_cpu_get_flag(FLAG_CF)); fct_chk(!rvm_cpu_get_flag(FLAG_ZF));
    fct_chk(!rvm_cpu_get_flag(FLAG_SF)); fct_chk(!rvm_cpu_get_flag(FLAG_OF));


    /* Execute: cmp [esp+4],0x81 */
    rvm_mem_save32u(reg_esp + 4, 0x80);
    rvm_code_set_string_source(reader, "80 7c 24 04 81");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk(rvm_cpu_get_flag(FLAG_CF)); fct_chk(!rvm_cpu_get_flag(FLAG_ZF));
    fct_chk(rvm_cpu_get_flag(FLAG_SF)); fct_chk(!rvm_cpu_get_flag(FLAG_OF));


    /* Execute: cmp [esp+4],0x81 */
    rvm_mem_save32u(reg_esp + 4, 0x81);
    rvm_code_set_string_source(reader, "80 7c 24 04 81");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk(!rvm_cpu_get_flag(FLAG_CF)); fct_chk(rvm_cpu_get_flag(FLAG_ZF));
    fct_chk(!rvm_cpu_get_flag(FLAG_SF)); fct_chk(!rvm_cpu_get_flag(FLAG_OF));
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_inst_pop) {
    int result;
    Bit32u value = 0x12345678;
    Bit32u new_esp;

    /* Prerequisite */
    new_esp = reg_esp + 4;
    rvm_mem_save32u(reg_esp, value);
    fct_chk_neq_int(reg_ebp, value);

    /* Execute: pop ebp */
    rvm_code_set_string_source(reader, "5d");
    result = rvm_cycle_step(runner);

    /* Check */
    fct_chk_eq_int(result, SUCCESS);
    fct_chk_eq_int(reg_ebp, value);
    fct_chk_eq_int(reg_esp, new_esp);
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_step_mnemonic) {
    int result;
    char mnemonic[10];
    const char *mnemonics[] = {
      "lea", "and", "push", "sar", "xor", "mov", "inc", "sub", "cmp", "pop", NULL
    };
    const char **m;

    /* Set source. */
    rvm_code_set_file_source(reader, "sample/cycle_basic");

    for (m = mnemonics; *m != NULL; m++) {
      result = rvm_cycle_step(runner);
      fct_chk_eq_int(result, SUCCESS);
      rvm_cycle_get_executed_mnemonic(runner, &mnemonic, 10);
      fct_chk_eq_str(mnemonic, *m);
    }
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_steps) {
    int result;

    /* Set source. */
    rvm_code_set_file_source(reader, "sample/cycle_basic");

    while (SUCCESS == rvm_cycle_step(runner));
    fct_chk_eq_int(10, rvm_cycle_get_steps(runner));
  } FCT_TEST_END();

  FCT_TEST_BGN(cycle_step_mnemonic2) {
    int result;
    char mnemonic[10];
    int step = 0;
    const char *mnemonics[] = {
      "push", "mov", "and", "sub", "mov", "mov", "lea", "mov",
      "add", "shl", "add", "mov", "mov", "add", "test", "mov", "mov",
      "push", "mov", "push", "sub", "pop", "lea", "mov", "mov",
      "add", "pop", NULL
    };
    const char **m;

    /* Set source. */
    rvm_code_set_file_source(reader, "sample/cycle_more");

    for (m = mnemonics; *m != NULL; m++) {
      result = rvm_cycle_step(runner);
      fct_chk_eq_int(result, SUCCESS);
      rvm_cycle_get_executed_mnemonic(runner, &mnemonic, 10);
      fct_chk_eq_str(mnemonic, *m);
    }
  } FCT_TEST_END();

} FCTMF_FIXTURE_SUITE_END();
