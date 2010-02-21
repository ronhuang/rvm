#include "mem.h"


/**
 * Global memory.
 */
struct rvm_mem_t {
  Bit8u dummy;
} MEM;


/**
 * Reset memory.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_reset(void) {
  return FAIL;
}


/**
 * Save content of the field (Bit32u) to memory.
 * \param address the address of the memory to save to.
 * \param field the field containing the data to save.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_save32u(Bit32u address, Bit32u field) {
  return FAIL;
}


/**
 * Load memory content (Bit32u) to field
 * \param address the address of the memory to load.
 * \param field the field to load the content of the memory to.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_load32u(Bit32u address, Bit32u *field) {
  return FAIL;
}
