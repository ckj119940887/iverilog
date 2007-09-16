/*
 * Copyright (c) 1999 Stephen Williams (steve@icarus.com)
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
#ident "$Id: sys_table.c,v 1.26 2006/08/03 05:06:04 steve Exp $"
#endif

# include "vpi_config.h"
# include "vpi_user.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

extern void sys_convert_register();
extern void sys_fileio_register();
extern void sys_finish_register();
extern void sys_deposit_register();
extern void sys_display_register();
extern void sys_plusargs_register();
extern void sys_random_register();
extern void sys_random_mti_register();
extern void sys_readmem_register();
extern void sys_scanf_register();
extern void sys_time_register();
extern void sys_vcd_register();
extern void sys_vcdoff_register();

#ifdef HAVE_LIBZ
#ifdef HAVE_LIBBZ2
extern void sys_lxt_register();
#else
static void sys_lxt_register() { fputs("LXT support disabled since libbzip2 not available\n",stderr); exit(1); }
#endif
extern void sys_lxt2_register();
#else
static void sys_lxt_register() { fputs("LXT support disabled since zlib not available\n",stderr); exit(1); }
static void sys_lxt2_register() { fputs("LXT2 support disabled since zlib not available\n",stderr); exit(1); }
#endif

static void sys_lxt_or_vcd_register()
{
      int idx;
      struct t_vpi_vlog_info vlog_info;

      char*dumper;

	/* Get the dumper of choice from the IVERILOG_DUMPER
	   environment variable. */
      dumper = getenv("IVERILOG_DUMPER");
      if (dumper) {
	    char*cp = strchr(dumper,'=');
	    if (cp != 0)
		  dumper = cp + 1;

      } else {
	    dumper = "vcd";
      }

	/* Scan the extended arguments, looking for flags that select
	   major features. This can override the environment variable
	   settings. */
      vpi_get_vlog_info(&vlog_info);

      for (idx = 0 ;  idx < vlog_info.argc ;  idx += 1) {

	    if (strcmp(vlog_info.argv[idx],"-lxt") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-space") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-speed") == 0) {
		  dumper = "lxt";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt-none") == 0) {
		  dumper = "none";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt2") == 0) {
		  dumper = "lxt2";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt2-space") == 0) {
		  dumper = "lxt2";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt2-speed") == 0) {
		  dumper = "lxt2";

	    } else if (strcmp(vlog_info.argv[idx],"-lxt2-none") == 0) {
		  dumper = "none";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd") == 0) {
		  dumper = "vcd";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd-off") == 0) {
		  dumper = "none";

	    } else if (strcmp(vlog_info.argv[idx],"-vcd-none") == 0) {
		  dumper = "none";

	    }
      }

      if (strcmp(dumper, "vcd") == 0)
	    sys_vcd_register();

      else if (strcmp(dumper, "VCD") == 0)
	    sys_vcd_register();

      else if (strcmp(dumper, "lxt") == 0)
	    sys_lxt_register();

      else if (strcmp(dumper, "LXT") == 0)
	    sys_lxt_register();

      else if (strcmp(dumper, "lxt2") == 0)
	    sys_lxt2_register();

      else if (strcmp(dumper, "LXT2") == 0)
	    sys_lxt2_register();

      else if (strcmp(dumper, "none") == 0)
	    sys_vcdoff_register();

      else if (strcmp(dumper, "NONE") == 0)
	    sys_vcdoff_register();

      else {
	    fprintf(stderr, "system.vpi: Unknown dumper format: %s\n",
		    dumper);
	    sys_vcd_register();
      }
}

void (*vlog_startup_routines[])() = {
      sys_convert_register,
      sys_fileio_register,
      sys_finish_register,
      sys_deposit_register,
      sys_display_register,
      sys_plusargs_register,
      sys_random_register,
      sys_random_mti_register,
      sys_readmem_register,
      sys_scanf_register,
      sys_time_register,
      sys_lxt_or_vcd_register,
      0
};

