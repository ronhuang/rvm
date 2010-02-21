/**
 * Implementation of instruction runner.
 */

#include <stdlib.h>
#include <string.h>
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
  } op1, op2, imm;

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
    if (mod < 0x11) { /* Applies to only mod with 0x00, 0x01, 0x10. */
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
        break;
      }
    }
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    break;
  }

  /* Extra */
  switch (micro.extra) {
  case M_EA:
    op1.d = offset;
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    break;
  }

  /* Process operands */

  /* Save operands */
  switch (micro.save) {
  case S_Gd: /* Destination is a dword genral register. */
    cpu.gregs[reg].d = op1.d;
    break;

  default:
    /* Unsupported instruction */
    assert(0);
    break;
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
