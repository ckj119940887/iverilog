/*
 * Copyright (c) 2000-2005 Stephen Williams (steve@icarus.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#ifdef HAVE_CVS_IDENT
#ident "$Id: memory.c,v 1.1 2005/03/03 04:34:42 steve Exp $"
#endif

# include "config.h"
# include "priv.h"
# include <assert.h>

void show_memory(ivl_memory_t mem)
{
      fprintf(out, "  mem [%u] %s [%u] <root=%d>\n",
	      ivl_memory_width(mem),
	      ivl_memory_basename(mem),
	      ivl_memory_size(mem),
	      ivl_memory_root(mem));
}
