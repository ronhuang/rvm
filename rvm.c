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


#include <stdio.h>
#include "type.h"
#include "mem.h"
#include "cpu.h"
#include "code.h"
#include "cycle.h"


static const char HELP_STR[] = "\
Ron's x86 Virtual Machine (lite).\n\
\n\
This program reads a text file with x86 machine code. It will disassemble and\n\
execute the instructions. Registers and flags are also dumped for every step.\n\
\n\
Sample file:\n\
50                       # push eax\n\
c1 f8 02                 # sar eax,0x02\n\
34 2e                    # xor al,0x2e\n\
89 e5                    # mov ebp,esp\n\
\n\
Usage:\n\
  %s <sample_file>\n";


int main(int argc, const char *argv[])
{
  int i;
  rvm_code *reader;
  rvm_cycle *runner;
  char mnemonic[10];

  /* Show help. */
  if (argc != 2) {
    printf(HELP_STR, argv[0]);
    return 0;
  }

  /* Initialize code reader. */
  reader = rvm_code_new();
  if (!reader) {
    fprintf(stderr, "No memory.\n");
    return 1;
  }
  if (SUCCESS != rvm_code_set_file_source(reader, argv[1])) {
    fprintf(stderr, "Failed to set file source, %s.\n", argv[1]);
    return 1;
  }

  /* Initialize code runner. */
  runner = rvm_cycle_new();
  if (!runner) {
    fprintf(stderr, "No memory.\n");
    return 1;
  }
  if (SUCCESS != rvm_cycle_set_code(runner, reader)) {
    fprintf(stderr, "Failed to set code reader.\n");
    return 1;
  }

  /* Initialize memory and CPU. */
  rvm_mem_reset();
  rvm_cpu_reset();
  reg_eip = 0x00001000;
  reg_ebp = 0x00002000;
  reg_esp = 0x00003ffc;

  printf("Step 0: (Initial state)\n");
  rvm_cpu_dump();
  while (SUCCESS == rvm_cycle_step(runner)) {
    rvm_cycle_get_executed_mnemonic(runner, &mnemonic, 10);

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Step %d: %s\n", rvm_cycle_get_steps(runner), mnemonic);
    rvm_cpu_dump();
  }

  return 0;
}
