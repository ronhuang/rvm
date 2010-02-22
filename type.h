#ifndef __TYPE_H__
#define __TYPE_H__


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
  L_REG,         /** Operands are in opcode. */
};

/* Save field. */
enum {
  S_NOP = 0,     /** Skip this. */
  S_Gd,          /** General register (dword). */
  S_Ed,          /** Register or memory (dword). */
  S_PUSH,        /** Push data to stack. */
};

/* Extra field. */
enum {
  M_EMPTY = 0,   /** Empty. */
  M_EA,          /** Effective address. */
  M_EdIb,        /** Register or memory, followed by immediate data. */
  M_GRP,         /** Opcode extension group. */
};

/* Process field. */
enum {
  P_NOP = 0,     /** Skip this. */
  P_AND,         /** Logical AND. */
  P_SAR,         /** Arithmetic right shift. */
};


/** Define micro instruction */
typedef struct rvm_micro_t {
  int load;
  int process;
  int save;
  int extra;
  const char mnemonic[16];
} rvm_micro;


/** Define instruction */
typedef struct rvm_inst_t {
  const char *mnemonic;
} rvm_inst;


#endif /* __TYPE_H__ */
