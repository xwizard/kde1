/*
 * prompt.c: Routines for retrieving and setting a prompt.
 *
 * $Header: /home/kde/kdeutils/kfloppy/e2fs/lib/ss/prompt.c,v 1.1.1.1 1997/11/27 01:43:19 wuebben Exp $
 * $Locker:  $
 *
 * Copyright 1987, 1988 by MIT Student Information Processing Board
 *
 * For copyright information, see copyright.h.
 */

#include "copyright.h"
#include <stdio.h>
#include "ss_internal.h"

#ifdef __STDC__
void ss_set_prompt(int sci_idx, char *new_prompt)
#else
void ss_set_prompt(sci_idx, new_prompt)
     int sci_idx;
     char *new_prompt;
#endif
{
     ss_info(sci_idx)->prompt = new_prompt;
}

#ifdef __STDC__
char *ss_get_prompt(int sci_idx)
#else
char *ss_get_prompt(sci_idx)
     int sci_idx;
#endif
{
     return(ss_info(sci_idx)->prompt);
}
