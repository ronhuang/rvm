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


/**
 * Implementation of instruction runner.
 */

#include <stdlib.h>
#include <string.h>
#define NDEBUG
#include <assert.h>
#include "cycle.h"
#include "code.h"
#include "micro_table.h"
#include "cpu.h"


/**
 * Scaled index table.
 */
static Bit32u ZERO = 0;
static Bit32u *SCALED_INDEX[] = {
  &reg_eax, &reg_ecx, &reg_edx, &reg_ebx,
  &ZERO,    &reg_ebp, &reg_esi, &reg_edi
};


/**
 * Context of the instruction runner.
 */
struct rvm_cycle_t {
  rvm_code *reader;
  char mnemonic[16];
  int steps;
};

/**
 * Constructor.
 * \return Instance of the instruction runner.
 */
rvm_cycle *rvm_cycle_new(void) {
  rvm_cycle *runner = malloc(sizeof(rvm_cycle));
  if (!runner) {
    return NULL;
  }
  memset(runner, 0, sizeof(rvm_cycle));

  return runner;
}

/**
 * Destructor.
 * \param [in] runner an instance of the instruction runner.
 */
void rvm_cycle_finalize(rvm_cycle *runner) {
  if (!runner) {
    return;
  }

  if (runner) {
    free(runner);
  }
}

/**
 * Set code reader to fetch the instructions.
 * \param [in] runner an instance of the instruction runner.
 * \param [in] reader an instance of the code reader.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cycle_set_code(rvm_cycle *runner, rvm_code *reader) {
  if (!runner || !reader) {
    return FAIL;
  }

  runner->reader = reader;

  return SUCCESS;
}

/**
 * Execute a single instruction.
 * \param [in] runner an instance of the instruction runner.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_step(rvm_cycle *runner) {
  rvm_code *rd;

  rvm_micro micro = {0};

  Bit8u opcode;
  Bit8u modrm, mod, reg, rm;
  Bit8u sib, scale, index, base;
  Bit32u offset;

  Bit8s disp8;
  Bit16s disp16;
  Bit32s disp32;

  union {
    Bit8u b;
    Bit8s bs;
    Bit16u w;
    Bit16s ws;
    Bit32u d;
    Bit32s ds;
  } op1, op2, dst;

  /* Prepare. */
  if (!runner || !runner->reader) {
    return FAIL;
  }
  rd = runner->reader;
  memset(&runner->mnemonic, 0, sizeof(runner->mnemonic));

  /* Read next byte from code. */
  if (!rvm_code_read(rd, &opcode)) return FAIL;

  /* Don't support multi-byte opcode for the time being */
  if (0x0f == opcode) {
    return FAIL;
  }

  /* Fetch the corresponding micro instruction. */
  memcpy(&micro, &rvm_micro_table[opcode], sizeof(micro));
  /* Save the mnemonic of the instruction. */
  strncpy(runner->mnemonic, micro.mnemonic, sizeof(runner->mnemonic) - 1);

  /* Load operands */
  switch (micro.load) {
  case L_MODRM: /* Has ModR/M in the instruction. */
    /* Fetch ModR/M */
    if (!rvm_code_read(rd, &modrm)) return FAIL;
    /* Slice it. */
    mod = modrm >> 6;
    reg = (modrm >> 3) & 0x07;
    rm = modrm & 0x07;

    /* Look up effective address  */
    if (mod < 0x03) { /* Applies to only mod with 0x00, 0x01, 0x02. */
      switch ((mod << 3) | rm) {
      case 0x0c: /* [--][--]+disp8 */
        /* Refer to Table 2-3. 32-Bit Addressing Forms with the SIB Byte. */
        /* Fetch SIB */
        if (!rvm_code_read(rd, &sib)) return FAIL;
        /* Slice it */
        scale = sib >> 6;
        index = (sib >> 3) & 0x07;
        base = sib & 0x07;

        switch (base) {
        case 0x00: offset = reg_eax; break;
        case 0x01: offset = reg_ecx; break;
        case 0x02: offset = reg_edx; break;
        case 0x03: offset = reg_ebx; break;
        case 0x04: offset = reg_esp; break;
        case 0x05:
          if (mod == 0x00) rvm_code_read32u(rd, &offset);
          else offset = reg_ebp; /* FIXME: incorrect implementation. */
        case 0x06: offset = reg_esi; break;
        case 0x07: offset = reg_edi; break;
        }
        offset += *SCALED_INDEX[index] << scale;

        /* Fetch disp8 */
        if (!rvm_code_read8s(rd, &disp8)) return FAIL;
        offset += disp8;
        break;

      default:
        /* Unsupported effective address. */
        assert(0);
        return FAIL;
      }
    }

  DISPATCH_EXTRA:
    /* Extra */
    switch (micro.extra) {
    case M_EA: /* ModR/M points to effective address. */
      op1.d = offset;
      break;

    case M_GRP: /* ModR/M points to extend opcode groups. */
      /* Fetch the corresponding group micro instruction. */
      memcpy(&micro, &rvm_micro_group_table[micro.process][reg], sizeof(micro));
      /* Save the mnemonic of the instruction. */
      strncpy(runner->mnemonic, micro.mnemonic, sizeof(runner->mnemonic) - 1);
      goto DISPATCH_EXTRA;
      break;

    case M_EbIb: /* ModR/M specifies a register or memory (Bit8u), and has immediate data (Bit8u) following it. */
      /* Second operand. */
      if (!rvm_code_read8s(rd, &disp8)) return FAIL;
      op2.d = disp8;
      /* First operand. */
      if (mod == 0x03) op1.d = reg_8(rm); /* General register. */
      else rvm_mem_load32u(offset, &op1.d); /* Effective address memory. */
      break;

    case M_EdIb: /* ModR/M specifies a register or memory (Bit32u), and has immediate data (Bit8u) following it. */
      /* Second operand. */
      if (!rvm_code_read8s(rd, &disp8)) return FAIL;
      op2.d = disp8;
      /* First operand. */
      if (mod == 0x03) op1.d = reg_32(rm); /* General register. */
      else rvm_mem_load32u(offset, &op1.d); /* Effective address memory. */
      break;

    case M_Gd: /* ModR/M specifies a register (Bit32u). */
      op1.d = reg_32(reg);
      break;

    default:
      /* Unsupported instruction */
      assert(0);
      return FAIL;
    }
    break;

  case L_REGd: /* Operand is a register (Bit32u) specified in table. */
    op1.d = reg_32(micro.extra);
    break;

  case L_REGbIb: /* Operands are register (Bit8u) specified in table and an immediate data (Bit8u). */
    if (!rvm_code_read8s(rd, &disp8)) return FAIL;
    op2.d = disp8;
    op1.d = reg_32(micro.extra);
    break;

  case L_POP: /* Pop value from stack to the first operand. */
    if (!rvm_cpu_pop32u(&op1.d)) return FAIL;
    break;

  case L_NOP:
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    return FAIL;
  }

  /* Process operands */
  switch (micro.process) {
  case P_ANDd: /* Logical AND (Bit32u). */
    dst.d = op1.d & op2.d;
    rvm_cpu_set_flag(FLAG_CF, 0);
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, 0);
    op1.d = dst.d;
    break;

  case P_SUBd: /* Logical SUB (Bit32u). */
    dst.d = op1.d - op2.d;
    rvm_cpu_set_flag(FLAG_CF, op1.d < op2.d);
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, ((op1.b ^ op2.b) & (op1.b ^ dst.b)) & 0x80000000);
    op1.d = dst.d;
    break;

  case P_SARd: /* Arithmetic right shift (Bit32u). */
    __asm__ __volatile__("sar %%cl,%0"
                         :"=r"(dst.d)
                         :"0"(op1.d), "c"(op2.d)
                         );
    rvm_cpu_set_flag(FLAG_CF, (((Bit32s) op1.d) >> (op2.d - 1)) & 1);
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, 0);
    op1.d = dst.d;
    break;

  case P_XORb: /* Logical XOR (Bit8u). */
    dst.d = op1.d ^ op2.d;
    rvm_cpu_set_flag(FLAG_CF, 0);
    rvm_cpu_set_flag(FLAG_ZF, dst.b == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.b & 0x80);
    rvm_cpu_set_flag(FLAG_OF, 0);
    op1.d = dst.d;
    break;

  case P_CMPb: /* CMP (Bit8u). */
    dst.b = op1.b - op2.b;
    rvm_cpu_set_flag(FLAG_CF, op1.b < op2.b);
    rvm_cpu_set_flag(FLAG_ZF, dst.b == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.b & 0x80);
    rvm_cpu_set_flag(FLAG_OF, ((op1.b ^ op2.b) & (op1.b ^ dst.b)) & 0x80);
    break;

  case P_INCd: /* INC (Bit32u). */
    dst.d = op1.d + 1;
    /* No change in CF. */
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, dst.d == 0x80000000);
    op1.d = dst.d;
    break;

  case P_NOP:
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    return FAIL;
  }

  /* Save operands */
  switch (micro.save) {
  case S_Gd: /* Destination is a general register (Bit32u) specified in ModR/M. */
    reg_32(reg) = op1.d;
    break;

  case S_Ed: /* Destination is either a register or memory specified in ModR/M. */
    if (mod == 0x03) reg_32(rm) = op1.d; /* Register. */
    else rvm_mem_save32u(offset, op1.d); /* Effective address memory. */
    break;

  case S_PUSH: /* Push operand to stack. */
    rvm_cpu_push32u(op1.d);
    break;

  case S_REGd: /* Save destination to register (Bit32u) specified in table. */
    reg_32(micro.extra) = op1.d;
    break;

  case S_REGb: /* Save destination to register (Bit8u) specified in table. */
    reg_8(micro.extra) = op1.b;
    break;

  case S_NOP:
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    return FAIL;
  }

  /* Keep track how many instruction executed. */
  runner->steps++;

  return SUCCESS;
}

/**
 * Retrieve the instruction just executed.
 * \param [in] runner an instance of the instruction runner.
 * \param [out] mnemonic buffer to store the mnemonic.
 *                       It will always be null-terminated.
 * \param [in] size size of the buffer.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_get_executed_mnemonic(rvm_cycle *runner, char *mnemonic, int size) {
  /* Prepare. */
  if (!runner || !mnemonic || size < 1) {
    return FAIL;
  }
  strncpy(mnemonic, runner->mnemonic, size - 1); /* Reserve one byte for null. */

  return SUCCESS;
}

/**
 * Retrieve the number of executed instructions.
 * \return Number of executed instructions.
 */
int rvm_cycle_get_steps(rvm_cycle *runner) {
  /* Prepare. */
  if (!runner) {
    return 0;
  }

  return runner->steps;
}
