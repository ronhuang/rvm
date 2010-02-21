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

  if (runner->reader) {
    rvm_code_finalize(runner->reader);
    runner->reader = NULL;
  }

  if (runner) {
    free(runner);
  }
}

/**
 * Set source of the code to instruction runner.
 * \param [in] runner an instance of the instruction runner.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_cycle_set_source(rvm_cycle *runner, const char *source) {
  if (!runner || !source) {
    return FAIL;
  }

  /* Close existing code reader. */
  if (runner->reader) {
    rvm_code_finalize(runner->reader);
    runner->reader = NULL;
  }

  /* Open new code reader. */
  runner->reader = rvm_code_new();
  if (!runner->reader) {
    return FAIL;
  }
  if (!runner->reader || !rvm_code_set_source(runner->reader, source)) {
    return FAIL;
  }

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
