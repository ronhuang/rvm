#ifndef __CYCLE_H__
#define __CYCLE_H__

/**
 * Header file for instruction runner.
 */

#include "type.h"

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
 * Set source of the code to instruction runner.
 * \param [in] runner an instance of the instruction runner.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cycle_set_source(rvm_cycle *runner, const char *source);

/**
 * Execute a single instruction.
 * \param [in] runner an instance of the instruction runner.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_step(rvm_cycle *runner);

#endif /* __CYCLE_H__ */
