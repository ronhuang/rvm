#include <stdio.h>
#include "cpu.h"


static const char DUMP_TEMPLATE[] =
  "eax           0x%08x\n"
  "ecx           0x%08x\n"
  "edx           0x%08x\n"
  "ebx           0x%08x\n"
  "esp           0x%08x\n"
  "ebp           0x%08x\n"
  "esi           0x%08x\n"
  "edi           0x%08x\n"
  "eip           0x%08x\n"
  "eflags        0x%08x\n"
  "cs            0x%04x\n"
  "ss            0x%04x\n"
  "ds            0x%04x\n"
  "es            0x%04x\n"
  "fs            0x%04x\n"
  "gs            0x%04x\n";


/**
 * Global cpu state.
 */
struct rvm_cpu_t CPU = {0};


/**
 * Reset the CPU.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_reset(void) {
  reg_eax = reg_ecx = reg_edx = reg_ebx = 0;
  reg_esp = reg_ebp = reg_esi = reg_edi = 0;
  reg_eip = 0;
  CPU.flags = 0;
  reg_cs = reg_ss = reg_ds = reg_es = reg_fs = reg_gs = 0;
  return SUCCESS;
}


/**
 * Push field (Bit32u) onto stack.
 * \param [in] field the data to be pushed.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_push32u(Bit32u field) {
  Bit32u sp = reg_esp - 4;
  rvm_mem_save32u(sp, field);
  reg_esp = sp;
  return SUCCESS;
}


/**
 * Pop from stack to field (Bit32u).
 * \param [out] will contain the poped data.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_pop32u(Bit32u *field) {
  if (field) {
    rvm_mem_load32u(reg_esp, field);
  }
  reg_esp += 4;
  return SUCCESS;
}


/**
 * Dump the registers and flags to stdout.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cpu_dump(void) {
  printf(DUMP_TEMPLATE,
         reg_eax, reg_ecx, reg_edx, reg_ebx,
         reg_esp, reg_ebp, reg_esi, reg_edi,
         CPU.ip.d, CPU.flags,
         reg_cs, reg_ss, reg_ds, reg_es, reg_fs, reg_gs);
}
