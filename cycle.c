/**
 * Implementation of instruction decoder.
 */

#include "stdlib.h"
#include "decode.h"
#include "code.h"
#include "micro_table.h"

/**
 * Context of the instruction decoder.
 */
struct rvm_decode_t {
  rvm_code *reader;
};

/**
 * Constructor.
 * \return Instance of the instruction decoder.
 */
rvm_decode *rvm_decode_new(void) {
  rvm_decode *decoder = malloc(sizeof(rvm_decode));
  if (!decoder) {
    return NULL;
  }
  memset(decoder, 0, sizeof(rvm_decode));

  return decoder;
}

/**
 * Destructor.
 * \param [in] decoder an instance of the instruction decoder.
 */
void rvm_decode_finalize(rvm_decode *decoder) {
  if (!decoder) {
    return;
  }

  if (decoder->reader) {
    rvm_code_finalize(decoder->reader);
    decoder->reader = NULL;
  }

  if (decoder) {
    free(decoder);
  }
}

/**
 * Set source of the code to instruction decoder.
 * \param [in] decoder an instance of the instruction decoder.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_decode_set_source(rvm_decode *decoder, const char *source) {
  if (!decoder || !source) {
    return FAIL;
  }

  /* Close existing code reader. */
  if (decoder->reader) {
    rvm_code_finalize(decoder->reader);
    decoder->reader = NULL;
  }

  /* Open new code reader. */
  decoder->reader = rvm_code_new();
  if (!decoder->reader) {
    return FAIL;
  }
  if (!decoder->reader || !rvm_code_set_source(decoder->reader, source)) {
    return FAIL;
  }

  return SUCCESS;
}

/**
 * Decode and return the next instruction.
 * \param [in] decoder an instance of the instruction decoder.
 * \param [out] inst an instance of the decoded instruction.
 * \return SUCCESS if decodes an instruction, otherwise FAIL.
 */
int rvm_decode_next(rvm_decode *decoder, rvm_inst *inst) {
  Bit8u op;
  rvm_micro micro;
  rvm_code *rd;

  if (!decoder || !inst || !decoder->reader) {
    return FAIL;
  }
  rd = decoder->reader;

  if (!rvm_code_read(rd, &op)) {
    return FAIL;
  }

  if (0x0f == op) {
    /* FIXME: support multi-byte opcode */
    return FAIL;
  }

  micro = rvm_micro_table[op];
}
