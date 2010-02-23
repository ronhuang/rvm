#ifndef __CODE_H__
#define __CODE_H__


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
 * Set filename containing the source for code reader.
 * \param [in] reader an instance of the code reader.
 * \param [in] filename filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_code_set_file_source(rvm_code *reader, const char *filename);


/**
 * Set string as source for code reader.
 * \param [in] reader an instance of the code reader.
 * \param [in] string a NULL terminated string.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
 */
int rvm_code_set_string_source(rvm_code *reader, const char *string);


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
