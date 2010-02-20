#ifndef __CODE_H__
#define __CODE_H__


#include "type.h"


/**
 * Context for the code reader
 */
typedef struct rvm_code_t rvm_code;


/**
 * Constructor
 */
rvm_code *rvm_code_new(void);


/**
 * Destructor
 */
void rvm_code_finalize(rvm_code *reader);


/**
 * Set source for code reader
 */
int rvm_code_set_source(rvm_code *reader, const char *source);


/**
 * Read code
 */
Bit8u rvm_code_read(rvm_code *reader);


#endif /* __CODE_H__ */
