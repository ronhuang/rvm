#ifndef __MEM_H__
#define __MEM_H__

/**
 * Header file for memory.
 */

#include "type.h"


/**
 * Reset memory.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_reset(void);


/**
 * Save content of the field (Bit32u) to memory.
 * \param address the address of the memory to save to.
 * \param field the field containing the data to save.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_save32u(Bit32u address, Bit32u field);


/**
 * Load memory content (Bit8u) to field
 * \param address the address of the memory to load.
 * \param field the field to load the content of the memory to.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_load32u(Bit32u address, Bit32u *field);


#endif /* __MEM_H__ */
