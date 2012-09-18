/*
 * File:	grkelot.h
 *
 * Synopsis:	string -> greek ELOT928 string; 4-state FSM.
 *
 * Copyright (c) 1994 Angelo Haritsis. All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that the above copyright notice and this paragraph are duplicated in all
 * such forms and that any documentation, advertising materials, and other
 * materials related to such distribution and use acknowledge that the
 * software was developed by Angelo Haritsis.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * $Header: /home/kde/kdebase/kvt/grkelot.h,v 1.2 1997/04/23 20:00:14 kulow Exp $
 */

#ifndef _GRKELOT_H
#define _GRKELOT_H

#define GREEK_ELOT928	0
#define GREEK_IBM437	1

#ifdef __cplusplus
extern "C" {
#endif

/* --- Prototypes --- */
void greek_init(int greek_mode);
void greek_end(void);
void greek_reset(void);
int greek_xlat(char *s, int num_chars);
/* --- */

#ifdef __cplusplus
}
#endif

#endif	/* _GRKELOT_H */
