#ifndef __TYPE_H__
#define __TYPE_H__


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


/** Standard data types used */
/** Borrowed from DOSBox. */
typedef unsigned char Bit8u;
typedef signed char Bit8s;
typedef unsigned short Bit16u;
typedef signed short Bit16s;
typedef unsigned int Bit32u;
typedef signed int Bit32s;
typedef unsigned long long Bit64u;
typedef signed long long Bit64s;
typedef Bit32u Bitu;
typedef Bit32s Bits;


/** Define NULL */
#ifndef NULL
#define NULL (void *)0
#endif

/** Define SUCCESS */
#ifndef SUCCESS
#define SUCCESS 1
#endif

/** Define FAIL */
#ifndef FAIL
#define FAIL 0
#endif


/** Define field in micro instruction */
/* Load field. */
enum {
  L_NOP = 0,     /** Skip this. */
  L_MODRM,       /** Operands are in ModR/M. */
  L_REGd,        /** Operands is register specified in table (Bit32u). */
  L_REGbIb,      /** Operands is register specified in table (Bit8u) and immediate data (Bit8u). */
  L_POP,         /** Operand is from stack. */
};

/* Save field. */
enum {
  S_NOP = 0,     /** Skip this. */
  S_Gd,          /** General register specified in ModR/M (Bit32u). */
  S_Ed,          /** Register or memory specified in ModR/M (Bit32u). */
  S_PUSH,        /** Push data to stack. */
  S_REGb,        /** Register specified in table (Bit8u). */
  S_REGd,        /** Register specified in table (Bit32u). */
};

/* Extra field. */
enum {
  M_EMPTY = 0,   /** Empty. */
  M_EA,          /** Effective address. */
  M_EdIb,        /** Register or memory (Bit32u), followed by immediate data (Bit8u). */
  M_EbIb,        /** Register or memory (Bit8u), followed by immediate data (Bit8u). */
  M_Gd,          /** General register. */
  M_GRP,         /** Opcode extension group. */
};

/* Process field. */
enum {
  P_NOP = 0,     /** Skip this. */
  P_ANDd,        /** Logical AND (Bit32u). */
  P_SUBd,        /** Logical SUB (Bit32u). */
  P_SARd,        /** Arithmetic right shift (Bit32u). */
  P_XORb,        /** Logical XOR (Bit8u). */
  P_CMPb,        /** CMP (Bit8u). */
  P_INCd,        /** INC (Bit32u). */
};


/** Define micro instruction */
typedef struct rvm_micro_t {
  int load;
  int process;
  int save;
  int extra;
  const char mnemonic[16];
} rvm_micro;


#endif /* __TYPE_H__ */
