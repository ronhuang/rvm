/**
 * Implementation of instruction runner.
 */

#include <stdlib.h>
#include <string.h>
#include "cycle.h"
#include "code.h"
#include "micro_table.h"

/**
 * Context of the instruction runner.
 */
struct rvm_cycle_t {
  rvm_code *reader;
};

/**
 * Constructor.
 * \return Instance of the instruction runner.
 */
rvm_cycle *rvm_cycle_new(void) {
  rvm_cycle *runner = malloc(sizeof(rvm_cycle));
  if (!runner) {
    return NULL;
  }
  memset(runner, 0, sizeof(rvm_cycle));

  return runner;
}

/**
 * Destructor.
 * \param [in] runner an instance of the instruction runner.
 */
void rvm_cycle_finalize(rvm_cycle *runner) {
  if (!runner) {
    return;
  }

  if (runner) {
    free(runner);
  }
}

/**
 * Set code reader to fetch the instructions.
 * \param [in] runner an instance of the instruction runner.
 * \param [in] reader an instance of the code reader.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cycle_set_code(rvm_cycle *runner, rvm_code *reader) {
  if (!runner || !reader) {
    return FAIL;
  }

  runner->reader = reader;

  return SUCCESS;
}

/**
 * Execute a single instruction.
 * \param [in] runner an instance of the instruction runner.
 * \return SUCCESS if cycles an instruction, otherwise FAIL.
 */
int rvm_cycle_step(rvm_cycle *runner) {
  Bit8u op;
  rvm_micro micro;
  rvm_code *rd;

  if (!runner || !runner->reader) {
    return FAIL;
  }
  rd = runner->reader;

  if (!rvm_code_read(rd, &op)) {
    return FAIL;
  }

  if (0x0f == op) {
    /* FIXME: support multi-byte opcode */
    return FAIL;
  }

  micro = rvm_micro_table[op];
}
