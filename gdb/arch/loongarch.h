/*
   Copyright (C) 2021 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef ARCH_LOONGARCH_H
#define ARCH_LOONGARCH_H

#include "gdbsupport/tdesc.h"
#include "opcode/loongarch.h"

extern unsigned int loongarch_debug;

struct loongarch_gdbarch_features
{
  int rlen = 0;
  int fpu32 = 0;
  int fpu64 = 0;
  int lbt = 0;
  int lsx = 0;
  int lasx = 0;


  /* Equality operator.  */
  bool operator== (const struct loongarch_gdbarch_features &lhs) const
  {
    return (rlen == lhs.rlen);
  }

  /* Inequality operator.  */
  bool operator!= (const struct loongarch_gdbarch_features &lhs) const
  {
    return !((*this) == lhs);
  }

  /* Used by std::unordered_map to hash feature sets.  */
  std::size_t hash () const noexcept
  {
    std::size_t val = 0 << 5 | (rlen & 0x1f) << 0;
    return val;
  }
};


#ifdef GDBSERVER

/* Create and return a target description that is compatible with FEATURES.
   This is only used directly from the gdbserver where the created target
   description is modified after it is return.  */

target_desc_up loongarch_create_target_description
	(const struct loongarch_gdbarch_features features);

#else

/* Lookup an already existing target description matching FEATURES, or
   create a new target description if this is the first time we have seen
   FEATURES.  For the same FEATURES the same target_desc is always
   returned.  This is important when trying to lookup gdbarch objects as
   GDBARCH_LIST_LOOKUP_BY_INFO performs a pointer comparison on target
   descriptions to find candidate gdbarch objects.  */

const target_desc *loongarch_lookup_target_description
	(const struct loongarch_gdbarch_features features);

#endif /* GDBSERVER */

#endif
