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
 * Implementation for memory.
 *
 * A hash table is used to emulate the memory. The address (Bit32u) is
 * the key to the hash table, while the content (Bit32u) of the memory
 * is the value of the hash table.
 */

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "hashtable.h"


/**
 * Key structures for hashtable.
 */
struct key {
  Bit32u address;
};

/**
 * Value structures for hashtable.
 */
struct value {
  union {
    Bit8u b[4];
    Bit32u d;
  } data;
};

/**
 * Hash function for hashtable.
 */
static unsigned int hashfromkey(void *ky) {
  struct key *k = (struct key *)ky;
  return k->address;
}

/**
 * Equal function for hashtable.
 */
static int equalkeys(void *ky1, void *ky2) {
  struct key *k1 = (struct key *)ky1;
  struct key *k2 = (struct key *)ky2;
  return k1->address == k2->address;
}

/**
 * Type safety.
 */
DEFINE_HASHTABLE_INSERT(insert_some, struct key, struct value);
DEFINE_HASHTABLE_SEARCH(search_some, struct key, struct value);
DEFINE_HASHTABLE_REMOVE(remove_some, struct key, struct value);


/**
 * Global memory.
 */
static struct rvm_mem_t {
  struct hashtable *h;
} MEM;


/**
 * Reset memory.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_reset(void) {
  if (MEM.h) {
    hashtable_destroy(MEM.h, 1);
    MEM.h = NULL;
  }

  MEM.h = create_hashtable(16, hashfromkey, equalkeys);
  if (NULL == MEM.h)
    return FAIL;

  return SUCCESS;
}


/**
 * Save content of the field (Bit32u) to memory.
 * \param address the address of the memory to save to.
 * \param field the field containing the data to save.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_save32u(Bit32u address, Bit32u field) {
  struct key *k;
  struct value *v;

  if (NULL == MEM.h) {
    fprintf(stderr, "hashtable not initialized.\n");
    return FAIL;
  }
  if (address != (address & 0xfffffffc)) {
    /* Alignment */
    return FAIL;
  }

  k = (struct key *)malloc(sizeof(struct key));
  if (!k) {
    return FAIL;
  }
  v = (struct value *)malloc(sizeof(struct value));
  if (!v) {
    free(k);
    return FAIL;
  }

  k->address = address;
  v->data.d = field;

  if (!insert_some(MEM.h, k, v)) {
    free(k);
    free(v);
    return FAIL;
  }

  return SUCCESS;
}


/**
 * Load memory content (Bit32u) to field
 * \param address the address of the memory to load.
 * \param field the field to load the content of the memory to.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_mem_load32u(Bit32u address, Bit32u *field) {
  static struct key k;
  struct value *v;

  if (NULL == MEM.h) {
    fprintf(stderr, "hashtable not initialized.\n");
    return FAIL;
  }
  if (address != (address & 0xfffffffc)) {
    /* Alignment */
    return FAIL;
  }
  if (NULL == field) {
    return FAIL;
  }

  k.address = address;
  v = search_some(MEM.h, &k);
  if (v) {
    *field = v->data.d;
  }
  else {
    *field = 0;
  }

  return SUCCESS;
}
