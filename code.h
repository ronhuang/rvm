#ifndef __CODE_H__
#define __CODE_H__


/**
 * Contains the header for code reader.
 */


#include "type.h"


/**
 * Convenient macros
 */
#define rvm_code_read8u rvm_code_read


/**
 * Context for the code reader.
 */
typedef struct rvm_code_t rvm_code;


/**
 * Constructor.
 * \return The instance of the code reader.
 */
rvm_code *rvm_code_new(void);


/**
 * Destructor.
 * \param [in] reader an instance of the code reader.
 */
void rvm_code_finalize(rvm_code *reader);


/**
 * Set source for code reader.
 * \param [in] reader an instance of the code reader.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_code_set_source(rvm_code *reader, const char *source);


/**
 * Read a byte (Bit8u) of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_code_read(rvm_code *reader, Bit8u *code);


/**
 * Read a Bit8s of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_code_read8s(rvm_code *reader, Bit8s *code);


/**
 * Read a Bit32u of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_code_read32u(rvm_code *reader, Bit32u *code);


#endif /* __CODE_H__ */
