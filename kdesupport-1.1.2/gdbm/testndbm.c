/* testndbm.c - Driver program to test the ndbm interface routines. */

/*  This file is part of GDBM, the GNU data base manager, by Philip A. Nelson.
    Copyright (C) 1990, 1991, 1993  Free Software Foundation, Inc.

    GDBM is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2, or (at your option)
    any later version.

    GDBM is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GDBM; see the file COPYING.  If not, write to
    the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

    You may contact the author by:
       e-mail:  phil@cs.wwu.edu
      us-mail:  Philip A. Nelson
                Computer Science Department
                Western Washington University
                Bellingham, WA 98226
       
*************************************************************************/


/* include system configuration before all else. */
#include <config.h>

#include <stdio.h>
#include <sys/types.h>
#if HAVE_FILE_H
#include <sys/file.h>
#endif
#include <sys/stat.h>
#if HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef GNU
#include "ndbm.h"
#else
#include <ndbm.h>
#endif

#define TRUE  1
#define FALSE 0


/* The test program allows one to call all the routines plus the hash function.
   The commands are single letter commands.  The user is prompted for all other
   information.  The commands are q (quit), f (fetch), s (store), d (delete),
   1 (firstkey), n (nextkey) and h (hash function). */

int
main (argc, argv)
     int argc;
     char *argv[];
{

  char  cmd_ch;

  datum key_data;
  datum data_data;
  datum return_data;

  char key_line[500];
  char data_line[1000];

  DBM *dbm_file;

  char done = FALSE;

  char *file_name;

  /* Argument checking. */
  if (argc > 2)
    {
      printf ("Usage: %s [dbm-file] \n",argv[0]);
      exit (2);
    }

  if (argc > 1)
    {
      file_name = argv[1];
    }
  else
    {
      file_name = "junkndbm";
    }

  /* Initialize. */
  data_data.dptr = data_line;

  dbm_file = dbm_open (file_name, O_RDWR|O_CREAT, 00664);
  if (dbm_file == NULL)
    {
      printf ("dbm_open failed.\n");
      exit (2);
    }

  /* Welcome message. */
  printf ("\nWelcome to the gndbm test program.  Type ? for help.\n\n");
  
  while (!done)
    {
      printf ("com -> ");
      cmd_ch = getchar ();
      while (getchar () != '\n') /* Do nothing. */;
      switch (cmd_ch)
	{
	case 'q':
	  done = TRUE;
	  break;

	case 'f':
	  printf ("key -> ");
	  gets (key_line);
	  key_data.dptr = key_line;
	  key_data.dsize = strlen (key_line)+1;
	  return_data = dbm_fetch (dbm_file, key_data);
	  if (return_data.dptr != NULL)
	      printf ("data is ->%s\n\n", return_data.dptr);
	  else
	    printf ("No such item found.\n\n");
	  break;

	case 's':
	  printf ("key -> ");
	  gets (key_line);
	  key_data.dptr = key_line;
	  key_data.dsize = strlen (key_line)+1;
	  printf ("data -> ");
	  gets (data_line);
	  data_data.dsize = strlen (data_line)+1;
	  if (dbm_store (dbm_file, key_data, data_data, DBM_REPLACE) != 0)
	    printf ("Item not inserted. \n");
	  printf ("\n");
	  break;

	case 'd':
	  printf ("key -> ");
	  gets (key_line);
	  key_data.dptr = key_line;
	  key_data.dsize = strlen (key_line)+1;
	  if (dbm_delete (dbm_file, key_data) != 0)
	    printf ("Item not found or deleted\n");
	  printf ("\n");
	  break;

	case '1':
	  key_data = dbm_firstkey (dbm_file);
	  if (key_data.dptr != NULL)
	    {
	      return_data = dbm_fetch (dbm_file, key_data);
	      printf ("key is ->%s\n", key_data.dptr);
	      printf ("data is ->%s\n\n", return_data.dptr);
	    }
	  else
	    printf ("No such item found.\n\n");
	  break;


	case '2':
	  key_data = dbm_nextkey (dbm_file);
	  if (key_data.dptr != NULL)
	    {
	      return_data = dbm_fetch (dbm_file, key_data);
	      printf ("key is ->%s\n", key_data.dptr);
	      printf ("data is ->%s\n\n", return_data.dptr);
	    }
	  else
	    printf ("No such item found.\n\n");
	  break;

	case 'c':
	  {
	    int temp;
	    temp = 0;
	    return_data = dbm_firstkey (dbm_file);
	    while (return_data.dptr != NULL)
	      {
		temp++;
		return_data = dbm_nextkey (dbm_file);
	      }
	    printf ("There are %d items in the database.\n\n", temp);
	  }
	  break;

	case '?':
	  printf ("c - count elements\n");
	  printf ("d - delete\n");
	  printf ("f - fetch\n");
	  printf ("q - quit\n");
	  printf ("s - store\n");
	  printf ("1 - firstkey\n");
	  printf ("2 - nextkey on last return value\n\n");
	  break;

	default:
	  printf ("What? \n\n");
	  break;

	}
    }

  /* Quit normally. */
  dbm_close (dbm_file);
  exit (0);

}
