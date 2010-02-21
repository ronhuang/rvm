/**
 * Actual implementation for code reader.
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "code.h"


/** Maximum length for the buffer.  */
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
 * Constructor.
 * \return The instance of the code reader.
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
 * Destructor.
 * \param [in] reader an instance of the code reader.
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
 * Set source for code reader.
 * \param [in] reader an instance of the code reader.
 * \param [in] source filename to file containing the code.
 * \return SUCCESS if the source is successfully set, otherwise FAIL.
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
 * Read a byte (Bit8u) of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
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


/**
 * Read a Bit8s of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_code_read8s(rvm_code *reader, Bit8s *code) {
  Bit8u p0;

  if (!reader || !code) {
    return FAIL;
  }

  if (!rvm_code_read(reader, &p0)) return FAIL;
  *code = (Bit8s)p0;

  return SUCCESS;
}


/**
 * Read a Bit32u of code from the source.
 * \param [in] reader an instance of the code reader.
 * \param [out] code to store the read code.
 * \return SUCCESS if reads a byte from source, otherwise FAIL.
 */
int rvm_code_read32u(rvm_code *reader, Bit32u *code) {
  Bit8u p0, p1, p2, p3;

  if (!reader || !code) {
    return FAIL;
  }

  if (!rvm_code_read(reader, &p0)) return FAIL;
  if (!rvm_code_read(reader, &p1)) return FAIL;
  if (!rvm_code_read(reader, &p2)) return FAIL;
  if (!rvm_code_read(reader, &p3)) return FAIL;

  /* Little-endian */
  *code = (p3 << 24) | (p2 << 16) | (p1 << 8) | p0;

  return SUCCESS;
}
