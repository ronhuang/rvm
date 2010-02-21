#ifndef __DECODE_H__
#define __DECODE_H__

/**
 * Header file for instruction decoder.
 */

#include "type.h"

/**
 * Context of the instruction decoder.
 */
typedef struct rvm_decode_t rvm_decode;

/**
 * Constructor.
 * \return Instance of the instruction decoder.
 */
rvm_decode *rvm_decode_new(void);

/**
 * Destructor.
 * \param [in] decoder an instance of the instruction decoder.
 */
void rvm_decode_finalize(rvm_decode *decoder);

/**
 * Set source of the code to instruction decoder.
 * \param [in] decoder an instance of the instruction decoder.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_decode_set_source(rvm_decode *decoder, const char *source);

/**
 * Decode and return the next instruction.
 * \param [in] decoder an instance of the instruction decoder.
 * \param [out] inst an instance of the decoded instruction.
 * \return SUCCESS if decodes an instruction, otherwise FAIL.
 */
int rvm_decode_next(rvm_decode *decoder, rvm_inst *inst);

#endif /* __DECODE_H__ */
