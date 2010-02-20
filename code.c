#include <stdlib.h>
#include <string.h>
#include "code.h"


/**
 * Context for the code reader
 */
struct rvm_code_t {
  const char *source;
};


/**
 * Constructor
 */
rvm_code *rvm_code_new(void) {
  rvm_code *reader = malloc(sizeof(rvm_code));
  if (reader) {
    memset(reader, 0, sizeof(rvm_code));
  }
  return reader;
}


/**
 * Destructor
 */
void rvm_code_finalize(rvm_code *reader) {
  if (reader) {
    free(reader);
  }
}


/**
 * Set source for code reader
 */
int rvm_code_set_source(rvm_code *reader, const char *source) {
}


/**
 * Read code
 */
Bit8u rvm_code_read(rvm_code *reader) {
}
