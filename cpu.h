#ifndef __CPU_H__
#define __CPU_H__


#include "type.h"


/**
 * General register index.
 */
enum {
  REG_AX, REG_CX, REG_DX, REG_BX, REG_SP, REG_BP, REG_SI, REG_DI
};

/**
 * Segment register index.
 */
enum {
  REG_CS, REG_SS, REG_DS, REG_ES, REG_FS, REG_GS
};


/**
 * Contains the necessary registers and flags for IA-32.
 */
struct rvm_cpu_t {
  union {
	Bit32u d;
	Bit16u w[2];
	Bit8u b[4];
  } gregs[8], ip;
  Bit32u flags;
  Bit16u sregs[6];
};


/**
 * Global cpu state.
 */
extern struct rvm_cpu_t cpu;


/**
 * Convenient macros for accessing registers.
 */
#define reg_eax cpu.gregs[REG_AX].d
#define reg_ecx cpu.gregs[REG_CX].d
#define reg_edx cpu.gregs[REG_DX].d
#define reg_ebx cpu.gregs[REG_BX].d
#define reg_esp cpu.gregs[REG_SP].d
#define reg_ebp cpu.gregs[REG_BP].d
#define reg_esi cpu.gregs[REG_SI].d
#define reg_edi cpu.gregs[REG_DI].d


#endif __CPU_H__
