/* libunwind - a platform-independent unwind library
   Copyright (C) 2003 Hewlett-Packard Co
	Contributed by David Mosberger-Tang <davidm@hpl.hp.com>

This file is part of libunwind.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

/* Utility to generate cursor_i.h.  */

#include <stdio.h>

#include "libunwind_i.h"

#ifdef offsetof
# undef offsetof
#endif

#define offsetof(type,field)	((char *) &((type *) 0)->field - (char *) 0)

static struct
  {
    const char name[256];
    unsigned long value;
  }
tab[] =
  {
    { "IP_OFF",		offsetof (struct cursor, ip) },
    { "PR_OFF",		offsetof (struct cursor, pr) },
    { "BSP_OFF",	offsetof (struct cursor, bsp) },
    { "PSP_OFF",	offsetof (struct cursor, psp) },
    { "PFS_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_PFS]) },
    { "RNAT_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_RNAT]) },
    { "UNAT_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_UNAT]) },
    { "LC_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_LC]) },
    { "FPSR_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_FPSR]) },
    { "B1_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_B1]) },
    { "B2_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_B2]) },
    { "B3_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_B3]) },
    { "B4_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_B4]) },
    { "B5_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_B5]) },
    { "F2_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_F2]) },
    { "F3_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_F3]) },
    { "F4_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_F4]) },
    { "F5_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_F5]) },
    { "FR_LOC_OFF",	offsetof (struct cursor, loc[IA64_REG_F16]) },
    { "LOC_SIZE",
      (offsetof (struct cursor, loc[1]) - offsetof (struct cursor, loc[0]))
    },
    { "SIGCONTEXT_ADDR_OFF",	offsetof (struct cursor, sigcontext_addr) },
};

static const char *tabs = "\t\t\t\t\t\t\t\t\t\t";

int
main (int argc, char **argv)
{
  const char *space;
  int i, num_tabs;
  size_t len;

  printf ("#ifndef cursor_i_h\n");
  printf ("#define cursor_i_h\n\n");

  printf ("/*\n * DO NOT MODIFY\n *\n * This file was generated by "
	  "%s.\n *\n */\n\n", argv[0]);

  for (i = 0; i < (int) (sizeof (tab) / sizeof (tab[0])); ++i)
    {
      if (tab[i].name[0] == '\0')
	printf ("\n");
      else
	{
	  len = strlen (tab[i].name);

	  num_tabs = (40 - len) / 8;
	  if (num_tabs <= 0)
	    space = " ";
	  else
	    space = strchr(tabs, '\0') - (40 - len) / 8;

	  printf ("#define %s%s%lu\t/* 0x%lx */\n",
		  tab[i].name, space, tab[i].value, tab[i].value);
	}
    }

  printf ("\n#endif /* cursor_i_h */\n");
  return 0;
}
