/* LoongArch-specific support for ELF.
   Copyright (C) 2021 Free Software Foundation, Inc.
   Contributed by Loongson Ltd.

   Based on RISC-V target.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3.  If not,
   see <http://www.gnu.org/licenses/>.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "elf-bfd.h"
#include "elf/loongarch.h"
#include "elfxx-loongarch.h"

#define ALL_ONES (~ (bfd_vma) 0)

/* This does not include any relocation information, but should be
   good enough for GDB or objdump to read the file.  */

static reloc_howto_type howto_table[] =
{
#define LOONGARCH_HOWTO(r_name)						 \
  HOWTO (R_LOONG_##r_name, 0, 2, 32, false, 0, complain_overflow_signed, \
	 bfd_elf_generic_reloc, "R_LOONG_" #r_name, false, 0, 0xffffffff, false)
  LOONGARCH_HOWTO (NONE),

  /* 32 bit relocation.  */
  HOWTO (R_LOONG_32,			/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_32",			/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  /* 64 bit relocation.  */
  HOWTO (R_LOONG_64,			/* type */
	 0,				/* rightshift */
	 4,				/* size */
	 64,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_64",			/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 ALL_ONES,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_RELATIVE,		/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_RELATIVE",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_COPY,			/* type */
	 0,				/* rightshift */
	 0,				/* this one is variable size */
	 0,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_bitfield,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_COPY",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0,				/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_JUMP_SLOT,		/* type */
	 0,				/* rightshift */
	 4,				/* size */
	 64,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_bitfield,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_JUMP_SLOT",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0,				/* dst_mask */
	 false),			/* pcrel_offset */

  /* Dynamic TLS relocations.  */
  HOWTO (R_LOONG_TLS_DTPMOD32,		/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_DTPMOD32",	/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_TLS_DTPMOD64,		/* type */
	 0,				/* rightshift */
	 4,				/* size */
	 64,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_DTPMOD64",	/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 ALL_ONES,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_TLS_DTPREL32,		/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_DTPREL32",	/* name */
	 true,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_TLS_DTPREL64,		/* type */
	 0,				/* rightshift */
	 4,				/* size */
	 64,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_DTPREL64",	/* name */
	 true,				/* partial_inplace */
	 0,				/* src_mask */
	 ALL_ONES,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_TLS_TPREL32,		/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_TPREL32",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_TLS_TPREL64,		/* type */
	 0,				/* rightshift */
	 4,				/* size */
	 64,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_TLS_TPREL64",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 ALL_ONES,			/* dst_mask */
	 false),			/* pcrel_offset */

  HOWTO (R_LOONG_IRELATIVE,		/* type */
	 0,				/* rightshift */
	 2,				/* size */
	 32,				/* bitsize */
	 false,				/* pc_relative */
	 0,				/* bitpos */
	 complain_overflow_dont,	/* complain_on_overflow */
	 bfd_elf_generic_reloc,		/* special_function */
	 "R_LOONG_IRELATIVE",		/* name */
	 false,				/* partial_inplace */
	 0,				/* src_mask */
	 0xffffffff,			/* dst_mask */
	 false),			/* pcrel_offset */

  LOONGARCH_HOWTO (MARK_LA),
  LOONGARCH_HOWTO (MARK_PCREL),
  HOWTO (R_LOONG_SOP_PUSH_PCREL,	      	/* type.  */
	 2,				   	/* rightshift.  */
	 2,				   	/* size.  */
	 32,				  	/* bitsize.  */
	 true /* FIXME: somewhat use this.  */,	/* pc_relative.  */
	 0,				   	/* bitpos.  */
	 complain_overflow_signed,	    	/* complain_on_overflow.  */
	 bfd_elf_generic_reloc,	       		/* special_function.  */
	 "R_LOONG_SOP_PUSH_PCREL",	    	/* name.  */
	 false,			       		/* partial_inplace.  */
	 0x03ffffff,			  	/* src_mask.  */
	 0x03ffffff,			  	/* dst_mask.  */
	 false),			      	/* pcrel_offset.  */
  LOONGARCH_HOWTO (SOP_PUSH_ABSOLUTE),
  LOONGARCH_HOWTO (SOP_PUSH_DUP),
  LOONGARCH_HOWTO (SOP_PUSH_GPREL),
  LOONGARCH_HOWTO (SOP_PUSH_TLS_TPREL),
  LOONGARCH_HOWTO (SOP_PUSH_TLS_GOT),
  LOONGARCH_HOWTO (SOP_PUSH_TLS_GD),
  LOONGARCH_HOWTO (SOP_PUSH_PLT_PCREL),
  LOONGARCH_HOWTO (SOP_ASSERT),
  LOONGARCH_HOWTO (SOP_NOT),
  LOONGARCH_HOWTO (SOP_SUB),
  LOONGARCH_HOWTO (SOP_SL),
  LOONGARCH_HOWTO (SOP_SR),
  LOONGARCH_HOWTO (SOP_ADD),
  LOONGARCH_HOWTO (SOP_AND),
  LOONGARCH_HOWTO (SOP_IF_ELSE),
  LOONGARCH_HOWTO (SOP_POP_32_S_10_5),
  LOONGARCH_HOWTO (SOP_POP_32_U_10_12),
  LOONGARCH_HOWTO (SOP_POP_32_S_10_12),
  LOONGARCH_HOWTO (SOP_POP_32_S_10_16),
  LOONGARCH_HOWTO (SOP_POP_32_S_10_16_S2),
  LOONGARCH_HOWTO (SOP_POP_32_S_5_20),
  LOONGARCH_HOWTO (SOP_POP_32_S_0_5_10_16_S2),
  LOONGARCH_HOWTO (SOP_POP_32_S_0_10_10_16_S2),
  LOONGARCH_HOWTO (SOP_POP_32_U),
  LOONGARCH_HOWTO (ADD8),
  LOONGARCH_HOWTO (ADD16),
  LOONGARCH_HOWTO (ADD24),
  LOONGARCH_HOWTO (ADD32),
  LOONGARCH_HOWTO (ADD64),
  LOONGARCH_HOWTO (SUB8),
  LOONGARCH_HOWTO (SUB16),
  LOONGARCH_HOWTO (SUB24),
  LOONGARCH_HOWTO (SUB32),
  LOONGARCH_HOWTO (SUB64),
};

struct elf_reloc_map
{
  bfd_reloc_code_real_type bfd_val;
  enum elf_loongarch_reloc_type elf_val;
};

static const struct elf_reloc_map larch_reloc_map[] =
{
  { BFD_RELOC_NONE, R_LOONG_NONE },
  { BFD_RELOC_32, R_LOONG_32 },
  { BFD_RELOC_64, R_LOONG_64 },

#define LOONGARCH_reloc_map(r_name)		   	\
  {						  	\
    BFD_RELOC_LOONG_##r_name, R_LOONG_##r_name		\
  }
  LOONGARCH_reloc_map (TLS_DTPMOD32),
  LOONGARCH_reloc_map (TLS_DTPMOD64),
  LOONGARCH_reloc_map (TLS_DTPREL32),
  LOONGARCH_reloc_map (TLS_DTPREL64),
  LOONGARCH_reloc_map (TLS_TPREL32),
  LOONGARCH_reloc_map (TLS_TPREL64),

  LOONGARCH_reloc_map (MARK_LA),
  LOONGARCH_reloc_map (MARK_PCREL),
  LOONGARCH_reloc_map (SOP_PUSH_PCREL),
  LOONGARCH_reloc_map (SOP_PUSH_ABSOLUTE),
  LOONGARCH_reloc_map (SOP_PUSH_DUP),
  LOONGARCH_reloc_map (SOP_PUSH_GPREL),
  LOONGARCH_reloc_map (SOP_PUSH_TLS_TPREL),
  LOONGARCH_reloc_map (SOP_PUSH_TLS_GOT),
  LOONGARCH_reloc_map (SOP_PUSH_TLS_GD),
  LOONGARCH_reloc_map (SOP_PUSH_PLT_PCREL),
  LOONGARCH_reloc_map (SOP_ASSERT),
  LOONGARCH_reloc_map (SOP_NOT),
  LOONGARCH_reloc_map (SOP_SUB),
  LOONGARCH_reloc_map (SOP_SL),
  LOONGARCH_reloc_map (SOP_SR),
  LOONGARCH_reloc_map (SOP_ADD),
  LOONGARCH_reloc_map (SOP_AND),
  LOONGARCH_reloc_map (SOP_IF_ELSE),
  LOONGARCH_reloc_map (SOP_POP_32_S_10_5),
  LOONGARCH_reloc_map (SOP_POP_32_U_10_12),
  LOONGARCH_reloc_map (SOP_POP_32_S_10_12),
  LOONGARCH_reloc_map (SOP_POP_32_S_10_16),
  LOONGARCH_reloc_map (SOP_POP_32_S_10_16_S2),
  LOONGARCH_reloc_map (SOP_POP_32_S_5_20),
  LOONGARCH_reloc_map (SOP_POP_32_S_0_5_10_16_S2),
  LOONGARCH_reloc_map (SOP_POP_32_S_0_10_10_16_S2),
  LOONGARCH_reloc_map (SOP_POP_32_U),
  LOONGARCH_reloc_map (ADD8),
  LOONGARCH_reloc_map (ADD16),
  LOONGARCH_reloc_map (ADD24),
  LOONGARCH_reloc_map (ADD32),
  LOONGARCH_reloc_map (ADD64),
  LOONGARCH_reloc_map (SUB8),
  LOONGARCH_reloc_map (SUB16),
  LOONGARCH_reloc_map (SUB24),
  LOONGARCH_reloc_map (SUB32),
  LOONGARCH_reloc_map (SUB64),
};

reloc_howto_type *
loongarch_elf_rtype_to_howto (unsigned int r_type)
{
  size_t i;
  for (i = 0; i < ARRAY_SIZE (howto_table); i++)
    if (howto_table[i].type == r_type)
      return &howto_table[i];
  return NULL;
}

reloc_howto_type *
loongarch_reloc_type_lookup (bfd *abfd ATTRIBUTE_UNUSED,
			     bfd_reloc_code_real_type code)
{
  unsigned int i;
  for (i = 0; i < ARRAY_SIZE (larch_reloc_map); i++)
    if (larch_reloc_map[i].bfd_val == code)
      return loongarch_elf_rtype_to_howto ((int) larch_reloc_map[i].elf_val);

  return NULL;
}

reloc_howto_type *
loongarch_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED, const char *r_name)
{
  unsigned int i;

  for (i = 0; i < ARRAY_SIZE (howto_table); i++)
    if (howto_table[i].name && strcasecmp (howto_table[i].name, r_name) == 0)
      return &howto_table[i];

  return NULL;
}
