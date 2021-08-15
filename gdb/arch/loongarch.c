/* Copyright (C) 2021 Free Software Foundation, Inc.

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

#include "gdbsupport/common-defs.h"
#include "gdbsupport/common-regcache.h"
#include "arch/loongarch.h"

const char *loongarch_expedite_regs[] = { "r3", "pc", NULL };

unsigned int loongarch_debug = 0;

#include <../features/loongarch/base32.c>
#include <../features/loongarch/base64.c>
#include <../features/loongarch/fpu32.c>
#include <../features/loongarch/fpu64.c>
#include <../features/loongarch/lbt32.c>
#include <../features/loongarch/lbt64.c>
#include <../features/loongarch/lsx.c>
#include <../features/loongarch/lasx.c>

#ifndef GDBSERVER
#define STATIC_IN_GDB static
#else
#define STATIC_IN_GDB
#endif

STATIC_IN_GDB target_desc_up
loongarch_create_target_description (const struct loongarch_gdbarch_features features)
{
  gdb_assert (features.rlen == 32 || features.rlen == 64);

  target_desc_up tdesc = allocate_target_description ();

#ifndef IN_PROCESS_AGENT
  std::string arch_name = "loongarch";

  if (features.rlen == 32)
    {
      arch_name.append ("32");
    }
  else if (features.rlen == 64)
    arch_name.append ("64");
  else
    gdb_assert_not_reached ("rlen unknown");

  set_tdesc_architecture (tdesc.get (), arch_name.c_str ());
#endif

  int regnum = 0;

  if (features.rlen == 64)
    regnum = create_feature_loongarch_base64 (tdesc.get (), regnum);
  else if (features.rlen == 32)
    regnum = create_feature_loongarch_base32 (tdesc.get (), regnum);
  else
    gdb_assert_not_reached ("rlen unknown");

  if (features.fpu32)
    regnum = create_feature_loongarch_fpu32 (tdesc.get (), regnum);
  else if (features.fpu64)
    regnum = create_feature_loongarch_fpu64 (tdesc.get (), regnum);

  if (features.lbt && features.rlen == 32)
    regnum = create_feature_loongarch_lbt32 (tdesc.get (), regnum);
  else if (features.lbt && features.rlen == 64)
    regnum = create_feature_loongarch_lbt64 (tdesc.get (), regnum);

  if (features.lsx)
    regnum = create_feature_loongarch_lsx (tdesc.get (), regnum);

  if (features.lasx)
    regnum = create_feature_loongarch_lasx (tdesc.get (), regnum);

  return tdesc;
}

#ifndef GDBSERVER

/* Wrapper used by std::unordered_map to generate hash for feature set.  */
struct loongarch_gdbarch_features_hasher
{
  std::size_t
  operator() (const loongarch_gdbarch_features &features) const noexcept
  {
    return features.hash ();
  }
};

/* Cache of previously seen target descriptions, indexed by the feature set
   that created them.  */
static std::unordered_map<loongarch_gdbarch_features,
			  const target_desc_up,
			  loongarch_gdbarch_features_hasher> loongarch_tdesc_cache;

/* See arch/loongarch.h.  */

const target_desc *
loongarch_lookup_target_description (const struct loongarch_gdbarch_features features)
{
  /* Lookup in the cache.  If we find it then return the pointer out of
     the target_desc_up (which is a unique_ptr).  This is safe as the
     loongarch_tdesc_cache will exist until GDB exits.  */
  const auto it = loongarch_tdesc_cache.find (features);
  if (it != loongarch_tdesc_cache.end ())
    return it->second.get ();

  target_desc_up tdesc (loongarch_create_target_description (features));

  /* Add to the cache, and return a pointer borrowed from the
     target_desc_up.  This is safe as the cache (and the pointers
     contained within it) are not deleted until GDB exits.  */
  target_desc *ptr = tdesc.get ();
  loongarch_tdesc_cache.emplace (features, std::move (tdesc));
  return ptr;
}

#endif /* !GDBSERVER */
