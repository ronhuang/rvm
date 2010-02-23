#ifndef __CYCLE_H__
#define __CYCLE_H__

/**
 * Header file for instruction runner.
 */

#include "code.h"

/**
 * Context of the instruction runner.
 */
typedef struct rvm_cycle_t rvm_cycle;

/**
 * Constructor.
 * \return Instance of the instruction runner.
 */
rvm_cycle *rvm_cycle_new(void);

/**
 * Destructor.
 * \param [in] runner an instance of the instruction runner.
 */
void rvm_cycle_finalize(rvm_cycle *runner);

/**
 * Set code reader to fetch the instructions.
 * \param [in] runner an instance of the instruction runner.
 * \param [in] reader an instance of the code reader.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cycle_set_code(rvm_cycle *runner, rvm_code *reader);

/**
 * Execute a single instruction.
 * \param [in] runner an instance of the instruction runner.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_step(rvm_cycle *runner);

/**
 * Retrieve the mnemonic of instruction just executed.
 * \param [in] runner an instance of the instruction runner.
 * \param [out] mnemonic buffer to store the mnemonic.
 *                       It will always be null-terminated.
 * \param [in] size size of the buffer.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_get_executed_instruction(rvm_cycle *runner, char *mnemonic, int size);

/**
 * Retrieve the number of executed instructions.
 * \return Number of executed instructions.
 */
int rvm_cycle_get_steps(rvm_cycle *runner);

#endif /* __CYCLE_H__ */
