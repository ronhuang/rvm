#ifndef __MEM_H__
#define __MEM_H__


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
 * Header file for memory.
 */

#include "type.h"


/**
 * Reset memory.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_reset(void);


/**
 * Save content of the field (Bit32u) to memory.
 * \param address the address of the memory to save to.
 * \param field the field containing the data to save.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_save32u(Bit32u address, Bit32u field);


/**
 * Load memory content (Bit8u) to field
 * \param address the address of the memory to load.
 * \param field the field to load the content of the memory to.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_load32u(Bit32u address, Bit32u *field);


#endif /* __MEM_H__ */
