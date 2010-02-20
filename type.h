#ifndef __TYPE_H__
#define __TYPE_H__


/* Standard data types used */
/* Borrowed from DOSBox. */
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


/* Define NULL */
#ifndef NULL
#define NULL (void *)0
#endif

/* Define SUCCESS */
#ifndef SUCCESS
#define SUCCESS 1
#endif

/* Define FAIL */
#ifndef FAIL
#define FAIL 0
#endif


#if 0
/* Recommended structure for IA-32 instruction. */
struct IA-32instr {
  unsigned short opcode, prefixmask;
  char ilen; // instruction length.
  InterpreterFunctionPointer execute; //semantic routine

  struct {
    //general addr. computation:[Rbase+(Rindex << shmt)+ disp.]
    char mode;  // addressing mode, including register operand
    char Rbase; // base address register
    char Rindex;// index register
    char shmt;  // index scale factor
    long displacement;
  } operandRM;

  struct {
    char mode;  // either register or immediate.
    char regname;  // register number
    long immediate;// immediate value
  } operandRI;
} instr;
#endif


#endif /* __TYPE_H__ */
