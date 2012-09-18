/*  Copyright 1992 John Bovey, University of Kent at Canterbury.
 *
 *  You can do what you like with this source code as long as
 *  you don't try to make money out of it and you include an
 *  unaltered copy of this message (including the copyright).
 *
 * This module has been heavily modifiedby R. Nation
 * (nation@rocket.sanders.lockheed.com).
 * No additional restrictions are applied
 *
 * As usual, the author accepts no responsibility for anything, nor does
 * he guarantee anything whatsoever.
 */

/* LICENSE changed: all authors including but not limited to John Bovey
 * aggreed to distribute their code under the terms of the GPL
 */

/* @(#)xsetup.h	1.1 14/7/92 (UKC) */

#ifndef XSETUP_H
#define XSETUP_H

#define BIGGER 1
#define SMALLER 2
#define NUM_FONTS 6
#define DEFAULT_FONT 0

int init_display(int, char **);
void resize_window(int, int);
void change_window_name(char *);
void change_icon_name(char *);
void error(char *,...);
void set_geom_string(char *string);
extern void NewFont(int);
void adjust_cursor(int);

#endif /* XSETUP_H */
