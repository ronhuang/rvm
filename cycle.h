#ifndef __CYCLE_H__
#define __CYCLE_H__


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
