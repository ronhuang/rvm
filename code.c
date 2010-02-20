#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "code.h"


#define MAX_BUFFER_LENGTH 256


/**
 * Context for the code reader
 */
struct rvm_code_t {
  FILE *source;

  char *buffer;
  int buffer_position;
  int buffer_size;

  char in_comment;
};


/**
 * Constructor
 */
rvm_code *rvm_code_new(void) {
  rvm_code *reader = malloc(sizeof(rvm_code));
  if (!reader) {
    return NULL;
  }
  memset(reader, 0, sizeof(rvm_code));

  reader->buffer = malloc(MAX_BUFFER_LENGTH);
  if (!reader->buffer) {
    free(reader);
    return NULL;
  }

  return reader;
}


/**
 * Destructor
 */
void rvm_code_finalize(rvm_code *reader) {
  if (!reader) {
    return;
  }

  if (reader->buffer) {
    free(reader->buffer);
  }

  if (reader->source) {
    fclose(reader->source);
    reader->source = NULL;
  }

  if (reader) {
    free(reader);
  }
}


/**
 * Set source for code reader
 */
int rvm_code_set_source(rvm_code *reader, const char *source) {
  if (!reader || !source) {
    return FAIL;
  }

  /* Close existing file handle. */
  if (reader->source) {
    fclose(reader->source);
    reader->source = NULL;
  }

  /* Open new file handle. */
  reader->source = fopen(source, "rb");
  if (!reader->source) {
    return FAIL;
  }
  return SUCCESS;
}


/**
 * Read code
 */
int rvm_code_read(rvm_code *reader, Bit8u *code) {
  char raw[3];
  int raw_position = 0;

  if (!reader || !code || !reader->source || !reader->buffer) {
    return FAIL;
  }

  memset(raw, 0, sizeof(raw));

  while (raw_position < 2) {
    if (reader->buffer_position >= reader->buffer_size) {
      /* Read from file */
      char *ret = fgets(reader->buffer, MAX_BUFFER_LENGTH, reader->source);
      if (!ret) {
        /* Error or EOF, stop trying to read. */
        break;
      }

      reader->buffer_position = 0;
      reader->buffer_size = strlen(reader->buffer);
    }

    /* Consume the rest of the buffer */
    if (reader->in_comment) {
      if ('\n' == reader->buffer[reader->buffer_size - 1]) {
        reader->in_comment = 0;
      }
      reader->buffer_position = reader->buffer_size;
    }

    if (reader->buffer_position < reader->buffer_size) {
      char ret = reader->buffer[reader->buffer_position++];

      if (isxdigit(ret)) {
        raw[raw_position++] = ret;
      }
      else if ('#' == ret) {
        reader->in_comment = 1;
      }
      else if ('\n' == ret) {
        reader->in_comment = 0;
      }
    }
  }

  if (raw_position != 2) {
    return FAIL;
  }

  *code = (Bit8u)strtol(raw, NULL, 16);
  return SUCCESS;
}
