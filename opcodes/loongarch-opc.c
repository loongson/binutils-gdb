/* loongarch opcode support.
   Copyright (C) 2021-2021 Free Software Foundation, Inc.
   Contributed by Loongson Ltd.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3. If not,
   see <http://www.gnu.org/licenses/>.  */

#include <stddef.h>
#include "opcode/loongarch.h"

struct loongarch_ASEs_option LARCH_opts =
{
  .ase_test = 0,
  .ase_fix = 0,
  .ase_float = 0,
  .ase_128vec = 0,
  .ase_256vec = 0,

  .addrwidth_is_32 = 0,
  .addrwidth_is_64 = 0,
  .rlen_is_32 = 0,
  .rlen_is_64 = 0,
  .la_local_with_abs = 0,
  .la_global_with_pcrel = 0,
  .la_global_with_abs = 0,

  .abi_is_lp32 = 0,
  .abi_is_lp64 = 0,

  .use_community_syntax = 0,
};

size_t
loongarch_insn_length (insn_t insn)
{
  return insn ? 4 : 4; /* eliminate warning */
}

const char *const loongarch_r_normal_name[32] =
{
  "$r0",  "$r1",  "$r2",  "$r3",  "$r4",  "$r5",  "$r6",  "$r7",
  "$r8",  "$r9",  "$r10", "$r11", "$r12", "$r13", "$r14", "$r15",
  "$r16", "$r17", "$r18", "$r19", "$r20", "$r21", "$r22", "$r23",
  "$r24", "$r25", "$r26", "$r27", "$r28", "$r29", "$r30", "$r31",
};

const char *const loongarch_r_lp64_name[32] =
{
  "$zero", "$ra", "$tp", "$sp", "$a0", "$a1", "$a2", "$a3",
  "$a4",   "$a5", "$a6", "$a7", "$t0", "$t1", "$t2", "$t3",
  "$t4",   "$t5", "$t6", "$t7", "$t8", "$x",  "$fp", "$s0",
  "$s1",   "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$s8",
};

const char *const loongarch_r_lp64_name1[32] =
{
  "", "", "", "", "$v0", "$v1", "", "", "", "", "", "", "", "", "", "",
  "", "", "", "", "",    "",    "", "", "", "", "", "", "", "", "", "",
};

const char *const loongarch_f_normal_name[32] =
{
  "$f0",  "$f1",  "$f2",  "$f3",  "$f4",  "$f5",  "$f6",  "$f7",
  "$f8",  "$f9",  "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
  "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
  "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31",
};

const char *const loongarch_f_lp64_name[32] =
{
  "$fa0", "$fa1", "$fa2",  "$fa3",  "$fa4",  "$fa5",  "$fa6",  "$fa7",
  "$ft0", "$ft1", "$ft2",  "$ft3",  "$ft4",  "$ft5",  "$ft6",  "$ft7",
  "$ft8", "$ft9", "$ft10", "$ft11", "$ft12", "$ft13", "$ft14", "$ft15",
  "$fs0", "$fs1", "$fs2",  "$fs3",  "$fs4",  "$fs5",  "$fs6",  "$fs7",
};

const char *const loongarch_f_lp64_name1[32] =
{
  "$fv0", "$fv1", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
  "",     "",     "", "", "", "", "", "", "", "", "", "", "", "", "", "",
};

const char *const loongarch_c_normal_name[8] =
{
  "$fcc0", "$fcc1", "$fcc2", "$fcc3", "$fcc4", "$fcc5", "$fcc6", "$fcc7",
};

const char *const loongarch_cr_normal_name[4] =
{
  "$scr0",
  "$scr1",
  "$scr2",
  "$scr3",
};

const char *const loongarch_v_normal_name[32] =
{
  "$vr0",  "$vr1",  "$vr2",  "$vr3",  "$vr4",  "$vr5",  "$vr6",  "$vr7",
  "$vr8",  "$vr9",  "$vr10", "$vr11", "$vr12", "$vr13", "$vr14", "$vr15",
  "$vr16", "$vr17", "$vr18", "$vr19", "$vr20", "$vr21", "$vr22", "$vr23",
  "$vr24", "$vr25", "$vr26", "$vr27", "$vr28", "$vr29", "$vr30", "$vr31",
};

const char *const loongarch_x_normal_name[32] =
{
  "$xr0",  "$xr1",  "$xr2",  "$xr3",  "$xr4",  "$xr5",  "$xr6",  "$xr7",
  "$xr8",  "$xr9",  "$xr10", "$xr11", "$xr12", "$xr13", "$xr14", "$xr15",
  "$xr16", "$xr17", "$xr18", "$xr19", "$xr20", "$xr21", "$xr22", "$xr23",
  "$xr24", "$xr25", "$xr26", "$xr27", "$xr28", "$xr29", "$xr30", "$xr31",
};

static struct loongarch_opcode loongarch_macro_opcodes[] =
{
  /* match,    mask,       name, comm. name, format, comm. format, macro, include, exclude, pinfo */
  {0, 0, "li.w", NULL, "r,sc", NULL, "%f", 0, 0, 0},
  {0, 0, "li.d", NULL, "r,sc", NULL, "%f", 0, 0, 0},
  { 0, 0, "la", NULL, "r,la", NULL, "la.global %1,%2", 0, 0, 0 },

  { 0, 0, "la.global", NULL, "r,la", NULL, "la.pcrel %1,%2",
    &LARCH_opts.la_global_with_pcrel, 0, 0 },
  { 0, 0, "la.global", NULL, "r,r,la", NULL, "la.pcrel %1,%2,%3",
    &LARCH_opts.la_global_with_pcrel, 0, 0 },
  { 0, 0, "la.global", NULL, "r,la", NULL, "la.abs %1,%2", &LARCH_opts.la_global_with_abs,
    0, 0 },
  { 0, 0, "la.global", NULL, "r,r,la", NULL, "la.abs %1,%3",
    &LARCH_opts.la_global_with_abs, 0, 0 },
  { 0, 0, "la.global", NULL, "r,l", NULL, "la.got %1,%2", 0, 0, 0 },
  { 0, 0, "la.global", NULL, "r,r,l", NULL, "la.got %1,%2,%3", 0, 0, 0 },

  { 0, 0, "la.local", NULL, "r,la", NULL, "la.abs %1,%2", &LARCH_opts.la_local_with_abs, 0,
    0 },
  { 0, 0, "la.local", NULL, "r,r,la", NULL, "la.abs %1,%3", &LARCH_opts.la_local_with_abs,
    0, 0 },
  { 0, 0, "la.local", NULL, "r,la", NULL, "la.pcrel %1,%2", 0, 0, 0 },
  { 0, 0, "la.local", NULL, "r,r,la", NULL, "la.pcrel %1,%2,%3", 0, 0, 0 },

  { 0, 0, "la.abs", NULL, "r,la", NULL,
    "lu12i.w %1,%%abs(%2)>>12;"
    "ori %1,%1,%%abs(%2)&0xfff;",
    &LARCH_opts.addrwidth_is_32, 0, 0 },
  { 0, 0, "la.abs", NULL, "r,la", NULL,
    "lu12i.w %1,%%abs(%2)<<32>>44;"
    "ori %1,%1,%%abs(%2)&0xfff;"
    "lu32i.d %1,%%abs(%2)<<12>>44;"
    "lu52i.d %1,%1,%%abs(%2)>>52;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.pcrel", NULL, "r,la", NULL,
    "pcaddu12i %1,%%pcrel(%2+0x800)<<32>>44;"
    "addi.w %1,%1,%%pcrel(%2+4)-(%%pcrel(%2+4+0x800)>>12<<12);",
    &LARCH_opts.addrwidth_is_32, 0, 0 },

  { 0, 0, "la.pcrel", NULL, "r,la", NULL,
    "pcaddu12i %1,%%pcrel(%2+0x800)>>12;"
    "addi.d %1,%1,%%pcrel(%2+4)-(%%pcrel(%2+4+0x800)>>12<<12);",
    &LARCH_opts.addrwidth_is_64, 0, 0 },
  { 0, 0, "la.pcrel", NULL, "r,r,la", NULL,
    "pcaddu12i %1,(%%pcrel(%3)-(%%pcrel(%3+0x80000000)>>32<<32))<<32>>44;"
    "ori %2,$r0,(%%pcrel(%3+4)-(%%pcrel(%3+4+0x80000000)>>32<<32))&0xfff;"
    "lu32i.d %2,%%pcrel(%3+8+0x80000000)<<12>>44;"
    "lu52i.d %2,%2,%%pcrel(%3+12+0x80000000)>>52;"
    "add.d %1,%1,%2;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.got", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%gprel(%2))<<32>>44;"
    "ld.w "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%gprel(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%gprel(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_32, 0, 0 },

  { 0, 0, "la.got", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%gprel(%2))>>12;"
    "ld.d "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%gprel(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%gprel(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_64, 0, 0 },
  { 0, 0, "la.got", NULL, "r,r,l", NULL,
    "pcaddu12i "
    "%1,(%%pcrel(_GLOBAL_OFFSET_TABLE_)+%%gprel(%3)-((%%pcrel(_GLOBAL_OFFSET_"
    "TABLE_+0x80000000)+%%gprel(%3))>>32<<32))<<32>>44;"
    "ori "
    "%2,$r0,(%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%gprel(%3)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x80000000)+%%gprel(%3))>>32<<32))&0xfff;"
    "lu32i.d "
    "%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+8+0x80000000)+%%gprel(%3))<<12>>44;"
    "lu52i.d "
    "%2,%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+12+0x80000000)+%%gprel(%3))>>52;"
    "ldx.d %1,%1,%2;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.tls.le", NULL, "r,la", NULL,
    "lu12i.w %1,%%tprel(%2)>>12;"
    "ori %1,%1,%%tprel(%2)&0xfff",
    &LARCH_opts.addrwidth_is_32, 0, 0 },
  /* {0, 0, "la.tls.le", NULL, "r,la", NULL,
  * "lu12i.w %1,%%tprel(%2)>>12;"
  * "ori %1,%1,%%tprel(%2)&0xfff"
  * , &LARCH_opts.addrwidth_is_64, 0, 0}, */
  { 0, 0, "la.tls.le", NULL, "r,la", NULL,
    "lu12i.w %1,%%tprel(%2)<<32>>44;"
    "ori %1,%1,%%tprel(%2)&0xfff;"
    "lu32i.d %1,%%tprel(%2)<<12>>44;"
    "lu52i.d %1,%1,%%tprel(%2)>>52;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.tls.ie", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%tlsgot(%2))<<32>>44;"
    "ld.w "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgot(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%tlsgot(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_32, 0, 0 },

  { 0, 0, "la.tls.ie", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%tlsgot(%2))>>12;"
    "ld.d "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgot(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%tlsgot(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_64, 0, 0 },
  { 0, 0, "la.tls.ie", NULL, "r,r,l", NULL,
    "pcaddu12i "
    "%1,(%%pcrel(_GLOBAL_OFFSET_TABLE_)+%%tlsgot(%3)-((%%pcrel(_GLOBAL_OFFSET_"
    "TABLE_+0x80000000)+%%tlsgot(%3))>>32<<32))<<32>>44;"
    "ori "
    "%2,$r0,(%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgot(%3)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x80000000)+%%tlsgot(%3))>>32<<32))&0xfff;"
    "lu32i.d "
    "%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+8+0x80000000)+%%tlsgot(%3))<<12>>44;"
    "lu52i.d "
    "%2,%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+12+0x80000000)+%%tlsgot(%3))>>52;"
    "ldx.d %1,%1,%2;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.tls.ld", NULL, "r,l", NULL, "la.tls.gd %1,%2", 0, 0, 0 },
  { 0, 0, "la.tls.ld", NULL, "r,r,l", NULL, "la.tls.gd %1,%2,%3",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0, 0, "la.tls.gd", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%tlsgd(%2))<<32>>44;"
    "addi.w "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgd(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%tlsgd(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_32, 0, 0 },

  { 0, 0, "la.tls.gd", NULL, "r,l", NULL,
    "pcaddu12i %1,(%%pcrel(_GLOBAL_OFFSET_TABLE_+0x800)+%%tlsgd(%2))>>12;"
    "addi.d "
    "%1,%1,%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgd(%2)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x800)+%%tlsgd(%2))>>12<<12);",
    &LARCH_opts.addrwidth_is_64, 0, 0 },
  { 0, 0, "la.tls.gd", NULL, "r,r,l", NULL,
    "pcaddu12i "
    "%1,(%%pcrel(_GLOBAL_OFFSET_TABLE_)+%%tlsgd(%3)-((%%pcrel(_GLOBAL_OFFSET_"
    "TABLE_+0x80000000)+%%tlsgd(%3))>>32<<32))<<32>>44;"
    "ori "
    "%2,$r0,(%%pcrel(_GLOBAL_OFFSET_TABLE_+4)+%%tlsgd(%3)-((%%pcrel(_GLOBAL_"
    "OFFSET_TABLE_+4+0x80000000)+%%tlsgd(%3))>>32<<32))&0xfff;"
    "lu32i.d "
    "%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+8+0x80000000)+%%tlsgd(%3))<<12>>44;"
    "lu52i.d "
    "%2,%2,(%%pcrel(_GLOBAL_OFFSET_TABLE_+12+0x80000000)+%%tlsgd(%3))>>52;"
    "add.d %1,%1,%2;",
    &LARCH_opts.addrwidth_is_64, 0, 0 },

  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_fix_opcodes[] =
{
  /* match,    mask,       name, comm. name, format, comm. format, macro, include, exclude, pinfo */
  { 0x00001000, 0xfffffc00, "clo.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00001400, 0xfffffc00, "clz.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00001800, 0xfffffc00, "cto.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00001c00, 0xfffffc00, "ctz.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00002000, 0xfffffc00, "clo.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00002400, 0xfffffc00, "clz.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00002800, 0xfffffc00, "cto.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00002c00, 0xfffffc00, "ctz.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00003000, 0xfffffc00, "revb.2h", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00003400, 0xfffffc00, "revb.4h", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00003800, 0xfffffc00, "revb.2w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00003c00, 0xfffffc00, "revb.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00004000, 0xfffffc00, "revh.2w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00004400, 0xfffffc00, "revh.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00004800, 0xfffffc00, "bitrev.4b", "revbit.4b", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00004c00, 0xfffffc00, "bitrev.8b", "revbit.8b", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00005000, 0xfffffc00, "bitrev.w", "revbit.w", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00005400, 0xfffffc00, "bitrev.d", "revbit.d", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00005800, 0xfffffc00, "ext.w.h", "sext.h", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00005c00, 0xfffffc00, "ext.w.b", "sext.b", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00150000, 0xfffffc00, "move", NULL, "r0:5,r5:5", NULL, 0 /* or %1,%2,$r0 */, 0, 0, 0 },
  { 0x00006000, 0xfffffc00, "rdtimel.w", "rdtickl.w", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00006400, 0xfffffc00, "rdtimeh.w", "rdtickh.w", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00006800, 0xfffffc00, "rdtime.d", "rdtick.d", "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00006c00, 0xfffffc00, "cpucfg", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x00010000, 0xffff801f, "asrtle.d", "asrtle", "r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00018000, 0xffff801f, "asrtgt.d", "asrtgt", "r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00040000, 0xfffe0000, "alsl.w", "sladd.w", "r0:5,r5:5,r10:5,u15:2+1", "r0:5,r5:5,r10:5,u15:2", 0, 0, 0, 0 },
  { 0x00060000, 0xfffe0000, "alsl.wu", "sladd.wu", "r0:5,r5:5,r10:5,u15:2+1", "r0:5,r5:5,r10:5,u15:2", 0, 0, 0, 0 },
  { 0x00080000, 0xfffe0000, "bytepick.w", "catpick.w", "r0:5,r5:5,r10:5,u15:2", NULL, 0, 0, 0,0 },
  { 0x000c0000, 0xfffc0000, "bytepick.d", "catpick.d", "r0:5,r5:5,r10:5,u15:3", NULL, 0, 0, 0,0 },
  { 0x00100000, 0xffff8000, "add.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00108000, 0xffff8000, "add.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00110000, 0xffff8000, "sub.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00118000, 0xffff8000, "sub.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00120000, 0xffff8000, "slt", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00128000, 0xffff8000, "sltu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00130000, 0xffff8000, "maskeqz", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00138000, 0xffff8000, "masknez", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00140000, 0xffff8000, "nor", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00148000, 0xffff8000, "and", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00150000, 0xffff8000, "or", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00158000, 0xffff8000, "xor", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00160000, 0xffff8000, "orn", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00168000, 0xffff8000, "andn", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00170000, 0xffff8000, "sll.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00178000, 0xffff8000, "srl.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00180000, 0xffff8000, "sra.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00188000, 0xffff8000, "sll.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00190000, 0xffff8000, "srl.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00198000, 0xffff8000, "sra.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001b0000, 0xffff8000, "rotr.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001b8000, 0xffff8000, "rotr.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001c0000, 0xffff8000, "mul.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001c8000, 0xffff8000, "mulh.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001d0000, 0xffff8000, "mulh.wu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001d8000, 0xffff8000, "mul.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001e0000, 0xffff8000, "mulh.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001e8000, 0xffff8000, "mulh.du", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001f0000, 0xffff8000, "mulw.d.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x001f8000, 0xffff8000, "mulw.d.wu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00200000, 0xffff8000, "div.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00208000, 0xffff8000, "mod.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00210000, 0xffff8000, "div.wu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00218000, 0xffff8000, "mod.wu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00220000, 0xffff8000, "div.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00228000, 0xffff8000, "mod.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00230000, 0xffff8000, "div.du", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00238000, 0xffff8000, "mod.du", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00240000, 0xffff8000, "crc.w.b.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00248000, 0xffff8000, "crc.w.h.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00250000, 0xffff8000, "crc.w.w.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00258000, 0xffff8000, "crc.w.d.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00260000, 0xffff8000, "crcc.w.b.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00268000, 0xffff8000, "crcc.w.h.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00270000, 0xffff8000, "crcc.w.w.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x00278000, 0xffff8000, "crcc.w.d.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x002a0000, 0xffff8000, "break", NULL, "u0:15", NULL, 0, 0, 0, 0 },
  { 0x002a8000, 0xffff8000, "dbcl", "dbgcall", "u0:15", NULL, 0, 0, 0, 0 },
  { 0x002b0000, 0xffff8000, "syscall", NULL, "u0:15", NULL, 0, 0, 0, 0 },
  { 0x002c0000, 0xfffe0000, "alsl.d", "sladd.d", "r0:5,r5:5,r10:5,u15:2+1", "r0:5,r5:5,r10:5,u15:2", 0, 0, 0, 0 },
  { 0x00408000, 0xffff8000, "slli.w", NULL, "r0:5,r5:5,u10:5", NULL, 0, 0, 0, 0 },
  { 0x00410000, 0xffff0000, "slli.d", NULL, "r0:5,r5:5,u10:6", NULL, 0, 0, 0, 0 },
  { 0x00448000, 0xffff8000, "srli.w", NULL, "r0:5,r5:5,u10:5", NULL, 0, 0, 0, 0 },
  { 0x00450000, 0xffff0000, "srli.d", NULL, "r0:5,r5:5,u10:6", NULL, 0, 0, 0, 0 },
  { 0x00488000, 0xffff8000, "srai.w", NULL, "r0:5,r5:5,u10:5", NULL, 0, 0, 0, 0 },
  { 0x00490000, 0xffff0000, "srai.d", NULL, "r0:5,r5:5,u10:6", NULL, 0, 0, 0, 0 },
  { 0x004c8000, 0xffff8000, "rotri.w", NULL, "r0:5,r5:5,u10:5", NULL, 0, 0, 0, 0 },
  { 0x004d0000, 0xffff0000, "rotri.d", NULL, "r0:5,r5:5,u10:6", NULL, 0, 0, 0, 0 },
  { 0x00600000, 0xffe08000, "bstrins.w", NULL, "r0:5,r5:5,u16:5,u10:5", NULL, 0, 0, 0, 0 },
  { 0x00608000, 0xffe08000, "bstrpick.w", NULL, "r0:5,r5:5,u16:5,u10:5", NULL, 0, 0, 0,0 },
  { 0x00800000, 0xffc00000, "bstrins.d", NULL, "r0:5,r5:5,u16:6,u10:6", NULL, 0, 0, 0, 0 },
  { 0x00c00000, 0xffc00000, "bstrpick.d", NULL, "r0:5,r5:5,u16:6,u10:6", NULL, 0, 0, 0,0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_float_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0x01008000, 0xffff8000, "fadd.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01010000, 0xffff8000, "fadd.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01028000, 0xffff8000, "fsub.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01030000, 0xffff8000, "fsub.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01048000, 0xffff8000, "fmul.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01050000, 0xffff8000, "fmul.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01068000, 0xffff8000, "fdiv.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01070000, 0xffff8000, "fdiv.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01088000, 0xffff8000, "fmax.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01090000, 0xffff8000, "fmax.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010a8000, 0xffff8000, "fmin.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010b0000, 0xffff8000, "fmin.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010c8000, 0xffff8000, "fmaxa.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010d0000, 0xffff8000, "fmaxa.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010e8000, 0xffff8000, "fmina.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x010f0000, 0xffff8000, "fmina.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01108000, 0xffff8000, "fscaleb.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01110000, 0xffff8000, "fscaleb.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01128000, 0xffff8000, "fcopysign.s", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01130000, 0xffff8000, "fcopysign.d", NULL, "f0:5,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x01140400, 0xfffffc00, "fabs.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01140800, 0xfffffc00, "fabs.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01141400, 0xfffffc00, "fneg.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01141800, 0xfffffc00, "fneg.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01142400, 0xfffffc00, "flogb.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01142800, 0xfffffc00, "flogb.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01143400, 0xfffffc00, "fclass.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01143800, 0xfffffc00, "fclass.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01144400, 0xfffffc00, "fsqrt.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01144800, 0xfffffc00, "fsqrt.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01145400, 0xfffffc00, "frecip.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01145800, 0xfffffc00, "frecip.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01146400, 0xfffffc00, "frsqrt.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01146800, 0xfffffc00, "frsqrt.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01149400, 0xfffffc00, "fmov.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01149800, 0xfffffc00, "fmov.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0114a400, 0xfffffc00, "movgr2fr.w", NULL, "f0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x0114a800, 0xfffffc00, "movgr2fr.d", NULL, "f0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x0114ac00, 0xfffffc00, "movgr2frh.w", NULL, "f0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x0114b400, 0xfffffc00, "movfr2gr.s", NULL, "r0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0114b800, 0xfffffc00, "movfr2gr.d", NULL, "r0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0114bc00, 0xfffffc00, "movfrh2gr.s", NULL, "r0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0114c000, 0xfffffc00, "movgr2fcsr", "fcsrwr", "r0:5,r5:5", "r5:5,u0:5", 0, 0, 0, 0 },
  { 0x0114c800, 0xfffffc00, "movfcsr2gr", "fcsrrd", "r0:5,r5:5", "r0:5,u5:5", 0, 0, 0, 0 },
  { 0x0114d000, 0xfffffc18, "movfr2cf", "movfr2fcc", "c0:3,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0114d400, 0xffffff00, "movcf2fr", "movfcc2fr", "f0:5,c5:3", NULL, 0, 0, 0, 0 },
  { 0x0114d800, 0xfffffc18, "movgr2cf", "movgr2fcc", "c0:3,r5:5", NULL, 0, 0, 0, 0 },
  { 0x0114dc00, 0xffffff00, "movcf2gr", "movfcc2gr", "r0:5,c5:3", NULL, 0, 0, 0, 0 },
  { 0x01191800, 0xfffffc00, "fcvt.s.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x01192400, 0xfffffc00, "fcvt.d.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a0400, 0xfffffc00, "ftintrm.w.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a0800, 0xfffffc00, "ftintrm.w.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a2400, 0xfffffc00, "ftintrm.l.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a2800, 0xfffffc00, "ftintrm.l.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a4400, 0xfffffc00, "ftintrp.w.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a4800, 0xfffffc00, "ftintrp.w.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a6400, 0xfffffc00, "ftintrp.l.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a6800, 0xfffffc00, "ftintrp.l.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a8400, 0xfffffc00, "ftintrz.w.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011a8800, 0xfffffc00, "ftintrz.w.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011aa400, 0xfffffc00, "ftintrz.l.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011aa800, 0xfffffc00, "ftintrz.l.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011ac400, 0xfffffc00, "ftintrne.w.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011ac800, 0xfffffc00, "ftintrne.w.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011ae400, 0xfffffc00, "ftintrne.l.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011ae800, 0xfffffc00, "ftintrne.l.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011b0400, 0xfffffc00, "ftint.w.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011b0800, 0xfffffc00, "ftint.w.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011b2400, 0xfffffc00, "ftint.l.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011b2800, 0xfffffc00, "ftint.l.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011d1000, 0xfffffc00, "ffint.s.w", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011d1800, 0xfffffc00, "ffint.s.l", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011d2000, 0xfffffc00, "ffint.d.w", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011d2800, 0xfffffc00, "ffint.d.l", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011e4400, 0xfffffc00, "frint.s", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x011e4800, 0xfffffc00, "frint.d", NULL, "f0:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_lmm_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0x02000000, 0xffc00000, "slti", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x02400000, 0xffc00000, "sltui", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x02800000, 0xffc00000, "addi.w", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x02c00000, 0xffc00000, "addi.d", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x03000000, 0xffc00000, "lu52i.d", "cu52i.d", "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0, 0, "nop", NULL, "", NULL, "andi $r0,$r0,0", NULL, 0, 0, 0 },
  { 0x03400000, 0xffc00000, "andi", NULL, "r0:5,r5:5,u10:12", NULL, 0, 0, 0, 0 },
  { 0x03800000, 0xffc00000, "ori", NULL, "r0:5,r5:5,u10:12", NULL, 0, 0, 0, 0 },
  { 0x03c00000, 0xffc00000, "xori", NULL, "r0:5,r5:5,u10:12", NULL, 0, 0, 0, 0 },
  { 0x10000000, 0xfc000000, "addu16i.d", NULL, "r0:5,r5:5,s10:16", NULL, 0, 0, 0, 0 },
  { 0x14000000, 0xfe000000, "lu12i.w", NULL, "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0x16000000, 0xfe000000, "lu32i.d", "cu32i.d", "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0x18000000, 0xfe000000, "pcaddi", "pcaddu2i", "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0x1a000000, 0xfe000000, "pcalau12i", NULL, "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0x1c000000, 0xfe000000, "pcaddu12i", NULL, "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0x1e000000, 0xfe000000, "pcaddu18i", NULL, "r0:5,s5:20", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_privilege_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0x04000000, 0xff0003e0, "csrrd", NULL, "r0:5,u10:14", NULL, 0, 0, 0, 0 },
  { 0x04000020, 0xff0003e0, "csrwr", NULL, "r0:5,u10:14", NULL, 0, 0, 0, 0 },
  { 0x04000000, 0xff000000, "csrxchg", NULL, "r0:5,r5:5,u10:14", NULL, 0, 0, 0, 0 },
  { 0x06000000, 0xffc00000, "cacop", NULL, "u0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x06400000, 0xfffc0000, "lddir", NULL, "r0:5,r5:5,u10:8", NULL, 0, 0, 0, 0 },
  { 0x06440000, 0xfffc001f, "ldpte", NULL, "r5:5,u10:8", NULL, 0, 0, 0, 0 },
  { 0x06480000, 0xfffffc00, "iocsrrd.b", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06480400, 0xfffffc00, "iocsrrd.h", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06480800, 0xfffffc00, "iocsrrd.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06480c00, 0xfffffc00, "iocsrrd.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06481000, 0xfffffc00, "iocsrwr.b", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06481400, 0xfffffc00, "iocsrwr.h", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06481800, 0xfffffc00, "iocsrwr.w", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06481c00, 0xfffffc00, "iocsrwr.d", NULL, "r0:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x06482000, 0xffffffff, "tlbclr", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06482400, 0xffffffff, "tlbflush", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06482800, 0xffffffff, "tlbsrch", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06482c00, 0xffffffff, "tlbrd", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06483000, 0xffffffff, "tlbwr", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06483400, 0xffffffff, "tlbfill", NULL, "", NULL, 0, 0, 0, 0 },
  { 0x06483800, 0xffffffff, "ertn", "eret", "", NULL, 0, 0, 0, 0 },
  { 0x06488000, 0xffff8000, "idle", NULL, "u0:15", NULL, 0, 0, 0, 0 },
  { 0x06498000, 0xffff8000, "invtlb", "tlbinv", "u0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_4opt_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0x08100000, 0xfff00000, "fmadd.s", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08200000, 0xfff00000, "fmadd.d", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08500000, 0xfff00000, "fmsub.s", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08600000, 0xfff00000, "fmsub.d", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08900000, 0xfff00000, "fnmadd.s", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08a00000, 0xfff00000, "fnmadd.d", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08d00000, 0xfff00000, "fnmsub.s", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x08e00000, 0xfff00000, "fnmsub.d", NULL, "f0:5,f5:5,f10:5,f15:5", NULL, 0, 0, 0, 0 },
  { 0x0c100000, 0xffff8018, "fcmp.caf.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c108000, 0xffff8018, "fcmp.saf.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c110000, 0xffff8018, "fcmp.clt.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c118000, 0xffff8018, "fcmp.slt.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c118000, 0xffff8018, "fcmp.sgt.s", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c120000, 0xffff8018, "fcmp.ceq.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c128000, 0xffff8018, "fcmp.seq.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c130000, 0xffff8018, "fcmp.cle.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c138000, 0xffff8018, "fcmp.sle.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c138000, 0xffff8018, "fcmp.sge.s", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c140000, 0xffff8018, "fcmp.cun.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c148000, 0xffff8018, "fcmp.sun.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c150000, 0xffff8018, "fcmp.cult.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c150000, 0xffff8018, "fcmp.cugt.s", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c158000, 0xffff8018, "fcmp.sult.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c160000, 0xffff8018, "fcmp.cueq.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c168000, 0xffff8018, "fcmp.sueq.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c170000, 0xffff8018, "fcmp.cule.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c170000, 0xffff8018, "fcmp.cuge.s", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c178000, 0xffff8018, "fcmp.sule.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c180000, 0xffff8018, "fcmp.cne.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c188000, 0xffff8018, "fcmp.sne.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c1a0000, 0xffff8018, "fcmp.cor.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c1a8000, 0xffff8018, "fcmp.sor.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c1c0000, 0xffff8018, "fcmp.cune.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c1c8000, 0xffff8018, "fcmp.sune.s", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c200000, 0xffff8018, "fcmp.caf.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c208000, 0xffff8018, "fcmp.saf.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c210000, 0xffff8018, "fcmp.clt.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c218000, 0xffff8018, "fcmp.slt.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c218000, 0xffff8018, "fcmp.sgt.d", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c220000, 0xffff8018, "fcmp.ceq.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c228000, 0xffff8018, "fcmp.seq.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c230000, 0xffff8018, "fcmp.cle.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c238000, 0xffff8018, "fcmp.sle.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c238000, 0xffff8018, "fcmp.sge.d", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c240000, 0xffff8018, "fcmp.cun.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c248000, 0xffff8018, "fcmp.sun.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c250000, 0xffff8018, "fcmp.cult.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c250000, 0xffff8018, "fcmp.cugt.d", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c258000, 0xffff8018, "fcmp.sult.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c260000, 0xffff8018, "fcmp.cueq.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c268000, 0xffff8018, "fcmp.sueq.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c270000, 0xffff8018, "fcmp.cule.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c270000, 0xffff8018, "fcmp.cuge.d", NULL, "c0:3,f10:5,f5:5", NULL, 0, 0, 0, 0 },
  { 0x0c278000, 0xffff8018, "fcmp.sule.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c280000, 0xffff8018, "fcmp.cne.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c288000, 0xffff8018, "fcmp.sne.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c2a0000, 0xffff8018, "fcmp.cor.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c2a8000, 0xffff8018, "fcmp.sor.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c2c0000, 0xffff8018, "fcmp.cune.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0c2c8000, 0xffff8018, "fcmp.sune.d", NULL, "c0:3,f5:5,f10:5", NULL, 0, 0, 0, 0 },
  { 0x0d000000, 0xfffc0000, "fsel", NULL, "f0:5,f5:5,f10:5,c15:3", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_load_store_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0x20000000, 0xff000000, "ll.w", NULL, "r0:5,r5:5,s10:14<<2", NULL, 0, 0, 0, 0 },
  { 0x21000000, 0xff000000, "sc.w", NULL, "r0:5,r5:5,s10:14<<2", NULL, 0, 0, 0, 0 },
  { 0x22000000, 0xff000000, "ll.d", NULL, "r0:5,r5:5,s10:14<<2", NULL, 0, 0, 0, 0 },
  { 0x23000000, 0xff000000, "sc.d", NULL, "r0:5,r5:5,s10:14<<2", NULL, 0, 0, 0, 0 },
  { 0x24000000, 0xff000000, "ldptr.w", "ldox4.w", "r0:5,r5:5,s10:14<<2", "r0:5,r5:5,s10:14", 0, 0, 0, 0 },
  { 0x25000000, 0xff000000, "stptr.w", "stox4.w", "r0:5,r5:5,s10:14<<2", "r0:5,r5:5,s10:14", 0, 0, 0, 0 },
  { 0x26000000, 0xff000000, "ldptr.d", "ldox4.d", "r0:5,r5:5,s10:14<<2", "r0:5,r5:5,s10:14", 0, 0, 0, 0 },
  { 0x27000000, 0xff000000, "stptr.d", "stox4.d", "r0:5,r5:5,s10:14<<2", "r0:5,r5:5,s10:14", 0, 0, 0, 0 },
  { 0x28000000, 0xffc00000, "ld.b", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x28400000, 0xffc00000, "ld.h", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x28800000, 0xffc00000, "ld.w", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x28c00000, 0xffc00000, "ld.d", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x29000000, 0xffc00000, "st.b", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x29400000, 0xffc00000, "st.h", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x29800000, 0xffc00000, "st.w", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x29c00000, 0xffc00000, "st.d", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2a000000, 0xffc00000, "ld.bu", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2a400000, 0xffc00000, "ld.hu", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2a800000, 0xffc00000, "ld.wu", NULL, "r0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2ac00000, 0xffc00000, "preld", NULL, "u0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2b000000, 0xffc00000, "fld.s", NULL, "f0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2b400000, 0xffc00000, "fst.s", NULL, "f0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2b800000, 0xffc00000, "fld.d", NULL, "f0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x2bc00000, 0xffc00000, "fst.d", NULL, "f0:5,r5:5,s10:12", NULL, 0, 0, 0, 0 },
  { 0x38000000, 0xffff8000, "ldx.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38040000, 0xffff8000, "ldx.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38080000, 0xffff8000, "ldx.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x380c0000, 0xffff8000, "ldx.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38100000, 0xffff8000, "stx.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38140000, 0xffff8000, "stx.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38180000, 0xffff8000, "stx.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x381c0000, 0xffff8000, "stx.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38200000, 0xffff8000, "ldx.bu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38240000, 0xffff8000, "ldx.hu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38280000, 0xffff8000, "ldx.wu", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x382c0000, 0xffff8000, "preldx", NULL, "u0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38300000, 0xffff8000, "fldx.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38340000, 0xffff8000, "fldx.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38380000, 0xffff8000, "fstx.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x383c0000, 0xffff8000, "fstx.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amswap.w", NULL, "r,r,r,u0:0", NULL, "amswap.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38600000, 0xffff8000, "amswap.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amswap.d", NULL, "r,r,r,u0:0", NULL, "amswap.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38608000, 0xffff8000, "amswap.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amadd.w", NULL, "r,r,r,u0:0", NULL, "amadd.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38610000, 0xffff8000, "amadd.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amadd.d", NULL, "r,r,r,u0:0", NULL, "amadd.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38618000, 0xffff8000, "amadd.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amand.w", NULL, "r,r,r,u0:0", NULL, "amand.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38620000, 0xffff8000, "amand.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amand.d", NULL, "r,r,r,u0:0", NULL, "amand.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38628000, 0xffff8000, "amand.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amor.w", NULL, "r,r,r,u0:0", NULL, "amor.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38630000, 0xffff8000, "amor.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amor.d", NULL, "r,r,r,u0:0", NULL, "amor.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38638000, 0xffff8000, "amor.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amxor.w", NULL, "r,r,r,u0:0", NULL, "amxor.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38640000, 0xffff8000, "amxor.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amxor.d", NULL, "r,r,r,u0:0", NULL, "amxor.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38648000, 0xffff8000, "amxor.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax.w", NULL, "r,r,r,u0:0", NULL, "ammax.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38650000, 0xffff8000, "ammax.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax.d", NULL, "r,r,r,u0:0", NULL, "ammax.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38658000, 0xffff8000, "ammax.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin.w", NULL, "r,r,r,u0:0", NULL, "ammin.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38660000, 0xffff8000, "ammin.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin.d", NULL, "r,r,r,u0:0", NULL, "ammin.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38668000, 0xffff8000, "ammin.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax.wu", NULL, "r,r,r,u0:0", NULL, "ammax.wu %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38670000, 0xffff8000, "ammax.wu", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax.du", NULL, "r,r,r,u0:0", NULL, "ammax.du %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38678000, 0xffff8000, "ammax.du", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin.wu", NULL, "r,r,r,u0:0", NULL, "ammin.wu %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38680000, 0xffff8000, "ammin.wu", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin.du", NULL, "r,r,r,u0:0", NULL, "ammin.du %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38688000, 0xffff8000, "ammin.du", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amswap_db.w", NULL, "r,r,r,u0:0", NULL, "amswap_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38690000, 0xffff8000, "amswap_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amswap_db.d", NULL, "r,r,r,u0:0", NULL, "amswap_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38698000, 0xffff8000, "amswap_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amadd_db.w", NULL, "r,r,r,u0:0", NULL, "amadd_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386a0000, 0xffff8000, "amadd_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amadd_db.d", NULL, "r,r,r,u0:0", NULL, "amadd_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386a8000, 0xffff8000, "amadd_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amand_db.w", NULL, "r,r,r,u0:0", NULL, "amand_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386b0000, 0xffff8000, "amand_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amand_db.d", NULL, "r,r,r,u0:0", NULL, "amand_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386b8000, 0xffff8000, "amand_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amor_db.w", NULL, "r,r,r,u0:0", NULL, "amor_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386c0000, 0xffff8000, "amor_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amor_db.d", NULL, "r,r,r,u0:0", NULL, "amor_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386c8000, 0xffff8000, "amor_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amxor_db.w", NULL, "r,r,r,u0:0", NULL, "amxor_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386d0000, 0xffff8000, "amxor_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "amxor_db.d", NULL, "r,r,r,u0:0", NULL, "amxor_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386d8000, 0xffff8000, "amxor_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax_db.w", NULL, "r,r,r,u0:0", NULL, "ammax_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386e0000, 0xffff8000, "ammax_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax_db.d", NULL, "r,r,r,u0:0", NULL, "ammax_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386e8000, 0xffff8000, "ammax_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin_db.w", NULL, "r,r,r,u0:0", NULL, "ammin_db.w %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386f0000, 0xffff8000, "ammin_db.w", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin_db.d", NULL, "r,r,r,u0:0", NULL, "ammin_db.d %1,%2,%3", NULL, 0, 0, 0 },
  { 0x386f8000, 0xffff8000, "ammin_db.d", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax_db.wu", NULL, "r,r,r,u0:0", NULL, "ammax_db.wu %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38700000, 0xffff8000, "ammax_db.wu", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammax_db.du", NULL, "r,r,r,u0:0", NULL, "ammax_db.du %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38708000, 0xffff8000, "ammax_db.du", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin_db.wu", NULL, "r,r,r,u0:0", NULL, "ammin_db.wu %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38710000, 0xffff8000, "ammin_db.wu", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0, 0, "ammin_db.du", NULL, "r,r,r,u0:0", NULL, "ammin_db.du %1,%2,%3", NULL, 0, 0, 0 },
  { 0x38718000, 0xffff8000, "ammin_db.du", NULL, "r0:5,r10:5,r5:5", NULL, 0, 0, 0, 0 },
  { 0x38720000, 0xffff8000, "dbar", NULL, "u0:15", NULL, 0, 0, 0, 0 },
  { 0x38728000, 0xffff8000, "ibar", NULL, "u0:15", NULL, 0, 0, 0, 0 },
  { 0x38740000, 0xffff8000, "fldgt.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38748000, 0xffff8000, "fldgt.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38750000, 0xffff8000, "fldle.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38758000, 0xffff8000, "fldle.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38760000, 0xffff8000, "fstgt.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38768000, 0xffff8000, "fstgt.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38770000, 0xffff8000, "fstle.s", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38778000, 0xffff8000, "fstle.d", NULL, "f0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38780000, 0xffff8000, "ldgt.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38788000, 0xffff8000, "ldgt.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38790000, 0xffff8000, "ldgt.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x38798000, 0xffff8000, "ldgt.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387a0000, 0xffff8000, "ldle.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387a8000, 0xffff8000, "ldle.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387b0000, 0xffff8000, "ldle.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387b8000, 0xffff8000, "ldle.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387c0000, 0xffff8000, "stgt.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387c8000, 0xffff8000, "stgt.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387d0000, 0xffff8000, "stgt.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387d8000, 0xffff8000, "stgt.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387e0000, 0xffff8000, "stle.b", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387e8000, 0xffff8000, "stle.h", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387f0000, 0xffff8000, "stle.w", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0x387f8000, 0xffff8000, "stle.d", NULL, "r0:5,r5:5,r10:5", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

static struct loongarch_opcode loongarch_jmp_opcodes[] =
{
  /* match,    mask,       name, format, macro, include, exclude, pinfo */
  { 0, 0, "bltz", NULL, "r,la", NULL, "bltz %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x60000000, 0xfc00001f, "bltz", NULL, "r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bgtz", NULL, "r,la", NULL, "bgtz %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x60000000, 0xfc0003e0, "bgtz", NULL, "r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bgez", NULL, "r,la", NULL, "bgez %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x64000000, 0xfc00001f, "bgez", NULL, "r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "blez", NULL, "r,la", NULL, "blez %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x64000000, 0xfc0003e0, "blez", NULL, "r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "beqz", NULL, "r,la", NULL, "beqz %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x40000000, 0xfc000000, "beqz", NULL, "r5:5,sb0:5|10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bnez", NULL, "r,la", NULL, "bnez %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x44000000, 0xfc000000, "bnez", NULL, "r5:5,sb0:5|10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bceqz", NULL, "c,la", NULL, "bceqz %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x48000000, 0xfc000300, "bceqz", NULL, "c5:3,sb0:5|10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bcnez", NULL, "c,la", NULL, "bcnez %1,%%pcrel(%2)", 0, 0, 0 },
  { 0x48000100, 0xfc000300, "bcnez", NULL, "c5:3,sb0:5|10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "jr", NULL, "r", NULL, "jirl $r0,%1,0", 0, 0, 0 },
  { 0, 0, "b", NULL, "la", NULL, "b %%pcrel(%1)", 0, 0, 0},
  { 0x50000000, 0xfc000000, "b", NULL, "sb0:10|10:16<<2", NULL, 0, 0, 0, 0},
  { 0x4c000000, 0xfc000000, "jirl", NULL, "r0:5,r5:5,s10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bl", NULL, "la", NULL, "bl %%pcrel(%1)", 0, 0, 0 },
  { 0x54000000, 0xfc000000, "bl", NULL, "sb0:10|10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "beq", NULL, "r,r,la", NULL, "beq %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x58000000, 0xfc000000, "beq", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bne", NULL, "r,r,la", NULL, "bne %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x5c000000, 0xfc000000, "bne", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "blt", NULL, "r,r,la", NULL, "blt %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x60000000, 0xfc000000, "blt", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bgt", NULL, "r,r,la", NULL, "bgt %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x60000000, 0xfc000000, "bgt", NULL, "r0:5,r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bge", NULL, "r,r,la", NULL, "bge %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x64000000, 0xfc000000, "bge", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "ble", NULL, "r,r,la", NULL, "ble %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x64000000, 0xfc000000, "ble", NULL, "r0:5,r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bltu", NULL, "r,r,la", NULL, "bltu %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x68000000, 0xfc000000, "bltu", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bgtu", NULL, "r,r,la", NULL, "bgtu %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x68000000, 0xfc000000, "bgtu", NULL, "r0:5,r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bgeu", NULL, "r,r,la", NULL, "bgeu %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x6c000000, 0xfc000000, "bgeu", NULL, "r5:5,r0:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0, 0, "bleu", NULL, "r,r,la", NULL, "bleu %1,%2,%%pcrel(%3)", 0, 0, 0 },
  { 0x6c000000, 0xfc000000, "bleu", NULL, "r0:5,r5:5,sb10:16<<2", NULL, 0, 0, 0, 0 },
  { 0 } /* Terminate the list.  */
};

struct loongarch_ase loongarch_ASEs[] =
{
  { &LARCH_opts.ase_fix, loongarch_macro_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_fix, loongarch_lmm_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_fix, loongarch_privilege_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_fix, loongarch_jmp_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_fix, loongarch_load_store_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_fix, loongarch_fix_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_float, loongarch_4opt_opcodes, 0, 0, { 0 }, 0, 0 },
  { &LARCH_opts.ase_float, loongarch_float_opcodes, 0, 0, { 0 }, 0, 0 },

  { 0 },
};
