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
  rvm_inst inst;
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
  memset(&runner->inst, 0, sizeof(rvm_inst));

  /* Read next byte from code. */
  if (!rvm_code_read(rd, &opcode)) return FAIL;

  /* Don't support multi-byte opcode for the time being */
  if (0x0f == opcode) {
    return FAIL;
  }

  /* Fetch the corresponding micro instruction. */
  memcpy(&micro, &rvm_micro_table[opcode], sizeof(micro));
  /* Save the mnemonic of the instruction. */
  runner->inst.mnemonic = micro.mnemonic;

  /* Load operands */
  switch (micro.load) {
  case L_MODRM: /* Involves register or memory */
    /* Fetch ModR/M */
    if (!rvm_code_read(rd, &modrm)) return FAIL;
    /* Slice it. */
    mod = modrm >> 6;
    reg = (modrm >> 3) & 0x07;
    rm = modrm & 0x07;

    /* Look up effective address  */
    if (mod < 0x03) { /* Applies to only mod with 0x00, 0x01, 0x02. */
      switch ((mod << 3) | rm) {
      case 0x0c:
        /* [--][--]+disp8 */
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
    case M_EA:
      op1.d = offset;
      break;

    case M_GRP:
      /* Fetch the corresponding group micro instruction. */
      memcpy(&micro, &rvm_micro_group_table[micro.process][reg], sizeof(micro));
      /* Save the mnemonic of the instruction. */
      runner->inst.mnemonic = micro.mnemonic;
      goto DISPATCH_EXTRA;
      break;

    case M_EbIb:
      /* Second operand. */
      if (!rvm_code_read8s(rd, &disp8)) return FAIL;
      op2.d = disp8;
      /* First operand. */
      if (mod == 0x03) op1.d = CPU.gregs[rm].b[0]; /* General register. */
      else rvm_mem_load32u(offset, &op1.d); /* Effective address memory. */
      break;

    case M_EdIb:
      /* Second operand. */
      if (!rvm_code_read8s(rd, &disp8)) return FAIL;
      op2.d = disp8;
      /* First operand. */
      if (mod == 0x03) op1.d = CPU.gregs[rm].d; /* General register. */
      else rvm_mem_load32u(offset, &op1.d); /* Effective address memory. */
      break;

    case M_Gd:
      op1.d = CPU.gregs[reg].d;
      break;

    default:
      /* Unsupported instruction */
      assert(0);
      return FAIL;
    }
    break;

  case L_REGd:
    op1.d = CPU.gregs[micro.extra].d;
    break;

  case L_REGbIb:
    if (!rvm_code_read8s(rd, &disp8)) return FAIL;
    op2.d = disp8;
    op1.d = CPU.gregs[micro.extra].d;
    break;

  case L_POP:
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
  case P_ANDd:
    dst.d = op1.d & op2.d;
    rvm_cpu_set_flag(FLAG_CF, 0);
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, 0);
    op1.d = dst.d;
    break;

  case P_SUBd:
    dst.d = op1.d - op2.d;
    rvm_cpu_set_flag(FLAG_CF, op1.d < op2.d);
    rvm_cpu_set_flag(FLAG_ZF, dst.d == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.d & 0x80000000);
    rvm_cpu_set_flag(FLAG_OF, ((op1.b ^ op2.b) & (op1.b ^ dst.b)) & 0x80000000);
    op1.d = dst.d;
    break;

  case P_SARd:
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

  case P_XORb:
    dst.d = op1.d ^ op2.d;
    rvm_cpu_set_flag(FLAG_CF, 0);
    rvm_cpu_set_flag(FLAG_ZF, dst.b == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.b & 0x80);
    rvm_cpu_set_flag(FLAG_OF, 0);
    op1.d = dst.d;
    break;

  case P_CMPb:
    dst.b = op1.b - op2.b;
    rvm_cpu_set_flag(FLAG_CF, op1.b < op2.b);
    rvm_cpu_set_flag(FLAG_ZF, dst.b == 0);
    rvm_cpu_set_flag(FLAG_SF, dst.b & 0x80);
    rvm_cpu_set_flag(FLAG_OF, ((op1.b ^ op2.b) & (op1.b ^ dst.b)) & 0x80);
    break;

  case P_INCd:
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
  case S_Gd: /* Destination is a dword general register. */
    CPU.gregs[reg].d = op1.d;
    break;

  case S_Ed:
    if (mod == 0x03) CPU.gregs[rm].d = op1.d; /* Register. */
    else rvm_mem_save32u(offset, op1.d); /* Effective address memory. */
    break;

  case S_PUSH: /* Push operand to stack. */
    rvm_cpu_push32u(op1.d);
    break;

  case S_REGd:
    CPU.gregs[micro.extra].d = op1.d;

  case S_REGb:
    CPU.gregs[micro.extra].b[0] = op1.b;
    break;

  case S_NOP:
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    return FAIL;
  }

  return SUCCESS;
}

/**
 * Retrieve the instruction just executed.
 * \param [in] runner an instance of the instruction runner.
 * \param [out] inst an instance of the instruction.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_get_executed_instruction(rvm_cycle *runner, rvm_inst *inst) {
  /* Prepare. */
  if (!runner) {
    return FAIL;
  }
  memcpy(inst, &runner->inst, sizeof(rvm_inst));

  return SUCCESS;
}
