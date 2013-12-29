/* 

    TiMidity -- Experimental MIDI to WAVE converter
    Copyright (C) 1995 Tuukka Toivonen <toivonen@clinet.fi>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    motif.h: written by Vincent Pagel (pagel@loria.fr) 10/4/95
   
    */

/* 
 * MESSAGE FROM KERNEL TO MOTIF
 */
#define REFRESH_MESSAGE 1
#define HELPMODE_MESSAGE 2
#define TOTALTIME_MESSAGE 3
#define MASTERVOL_MESSAGE 4
#define FILENAME_MESSAGE 5
#define CURTIME_MESSAGE 6
#define NOTE_MESSAGE 7
#define PROGRAM_MESSAGE 8
#define VOLUME_MESSAGE 9
#define EXPRESSION_MESSAGE 10
#define PANNING_MESSAGE 11
#define SUSTAIN_MESSAGE 12
#define PITCH_MESSAGE 13
#define RESET_MESSAGE 14
#define CLOSE_MESSAGE 15
#define CMSG_MESSAGE 16
#define FILE_LIST_MESSAGE 17
#define NEXT_FILE_MESSAGE 18
#define PREV_FILE_MESSAGE 19
#define TUNE_END_MESSAGE 20

/* 
 * MESSAGE ON THE PIPE FROM MOTIF TOWARD KERNEL
 */
#define MOTIF_CHANGE_VOLUME 1
#define MOTIF_CHANGE_LOCATOR 2
#define MOTIF_QUIT 3
#define MOTIF_PLAY_FILE 4
#define MOTIF_NEXT 5
#define MOTIF_PREV 6
#define MOTIF_RESTART 7
#define MOTIF_FWD 8
#define MOTIF_RWD 9
#define MOTIF_PAUSE 10


/*
 * CONSTANTS FOR MOTIF MENUS
 */
#define MENU_OPEN 1
#define MENU_QUIT 2
#define MENU_TOGGLE 3

#define DIALOG_CANCEL 1
#define DIALOG_OK 2
#define DIALOG_ALL 3


/*
 * Pipe function interfaces
 */
void pipe_int_write(int c);
void pipe_int_read(int *c);

void pipe_string_write(char *str);
void pipe_string_read(char *str);

void pipe_open();
int pipe_read_ready();

void Launch_Motif_Process(int pipe_number);

