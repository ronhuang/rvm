#ifndef __MICRO_TABLE_H__
#define __MICRO_TABLE_H__


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
 * Contains an incomplete table roughly equivalent to "Table
 * A-2. One-byte Opcode Map" in the Intel manual.
 *
 * Each entry in rvm_micro_table corresponds to an opcode or points to
 * an opcode extension group.
 *
 * Each entry in rvm_micro_group_table corresponds to an opcode
 * extension group, which includes the opcodes for that group.
 */

#include "type.h"
#include "cpu.h"

rvm_micro rvm_micro_table[] = {
  /* 0x00 ~ 0x07 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x08 ~ 0x0F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x10 ~ 0x17 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x18 ~ 0x1F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x20 ~ 0x27 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x28 ~ 0x2F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x30 ~ 0x37 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {L_REGbIb     ,P_XORb     ,S_REGb ,REG_AX ,"xor"        },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x38 ~ 0x3F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x40 ~ 0x47 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {L_REGd       ,P_INCd     ,S_REGd ,REG_BP ,"inc"        },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x48 ~ 0x4F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x50 ~ 0x57 */
  {L_REGd       ,0          ,S_PUSH ,REG_AX ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_CX ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_DX ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_BX ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_SP ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_BP ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_SI ,"push"       },
  {L_REGd       ,0          ,S_PUSH ,REG_DI ,"push"       },
  /* 0x58 ~ 0x5F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {L_POP        ,0          ,S_REGd ,REG_BP ,"pop"        },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x60 ~ 0x67 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x68 ~ 0x6F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x70 ~ 0x77 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x78 ~ 0x7F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x80 ~ 0x87 */
  {L_MODRM      ,0          ,0      ,M_GRP  },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {L_MODRM      ,1          ,0      ,M_GRP  },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x88 ~ 0x8F */
  {0            ,0          ,0      ,0      },
  {L_MODRM      ,0          ,S_Ed   ,M_Gd   ,"mov"        },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {L_MODRM      ,0          ,S_Gd   ,M_EA   ,"lea"        },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0x90 ~ 0x97 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0x98 ~ 0x9F */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xA0 ~ 0xA7 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xA8 ~ 0xAF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xB0 ~ 0xB7 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xB8 ~ 0xBF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xC0 ~ 0xC7 */
  {0            ,0          ,0      ,0      },
  {L_MODRM      ,2          ,0      ,M_GRP  },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xC8 ~ 0xCF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xD0 ~ 0xD7 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xD8 ~ 0xDF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xE0 ~ 0xE7 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xE8 ~ 0xEF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },

  /* 0xF0 ~ 0xF7 */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  /* 0xF8 ~ 0xFF */
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
  {0            ,0          ,0      ,0      },
};

rvm_micro rvm_micro_group_table[][8] = {
  /* 0, Group 1, 0x80, Eb, Ib */
  {
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,P_CMPb     ,0      ,M_EbIb     ,"cmp"        },
  },
  /* 1, Group 1, 0x83, Ev, Ib */
  {
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,P_ANDd     ,S_Ed   ,M_EdIb     ,"and"        },
    {0      ,P_SUBd     ,S_Ed   ,M_EdIb     ,"sub"        },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
  },
  /* 2, Group 2 */
  {
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,0          ,0      ,0          },
    {0      ,P_SARd     ,S_Ed   ,M_EdIb     ,"sar"        },
  },
};

#endif /* __MICRO_TABLE_H__ */
