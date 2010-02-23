#ifndef __CPU_H__
#define __CPU_H__


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
 * Flags masks.
 */
enum {
  FLAG_CF = 1 << 0,
  FLAG_ZF = 1 << 6,
  FLAG_SF = 1 << 7,
  FLAG_OF = 1 << 11,
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
extern struct rvm_cpu_t CPU;


/**
 * Convenient macros for accessing registers.
 */
#define reg_eax CPU.gregs[REG_AX].d
#define reg_al  CPU.gregs[REG_AX].b[0]

#define reg_ecx CPU.gregs[REG_CX].d
#define reg_cl  CPU.gregs[REG_CX].b[0]

#define reg_edx CPU.gregs[REG_DX].d
#define reg_dl  CPU.gregs[REG_DX].b[0]

#define reg_ebx CPU.gregs[REG_BX].d
#define reg_bl  CPU.gregs[REG_BX].b[0]

#define reg_esp CPU.gregs[REG_SP].d
#define reg_ebp CPU.gregs[REG_BP].d
#define reg_esi CPU.gregs[REG_SI].d
#define reg_edi CPU.gregs[REG_DI].d

#define reg_eip CPU.ip.d

#define reg_cs CPU.sregs[REG_CS]
#define reg_ss CPU.sregs[REG_SS]
#define reg_ds CPU.sregs[REG_DS]
#define reg_es CPU.sregs[REG_ES]
#define reg_fs CPU.sregs[REG_FS]
#define reg_gs CPU.sregs[REG_GS]

#define reg_32(reg) (CPU.gregs[(reg)].d)
#define reg_8(reg) (CPU.gregs[(reg)].b[0])


/**
 * Convenient macros for accessing flags.
 */
#define rvm_cpu_set_flag(mask, bit)                                     \
  do {                                                                  \
  if (bit) CPU.flags |= mask;                                           \
  else CPU.flags &= ~mask;                                              \
  } while (0)

#define rvm_cpu_get_flag(mask) ((CPU.flags & mask) ? 1 : 0)

/**
 * Reset the CPU.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_reset(void);


/**
 * Stack manipulation functions
 */
/**
 * Push field (Bit32u) onto stack.
 * \param [in] field the data to be pushed.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_push32u(Bit32u field);

/**
 * Pop from stack to field (Bit32u).
 * \param [out] will contain the poped data.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_pop32u(Bit32u *field);


/**
 * Dump the registers and flags to stdout.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_dump(void);


#endif /* __CPU_H__ */
