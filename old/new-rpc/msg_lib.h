/*
 *    msg_lib.h
 *
 *    Copyright (C) 2002  <Chris Nystrom>
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *    Contact Author at:
 *
 *    Chris Nystrom
 *
 *    Soli Deo Gloria
 *
 */

#ifndef MSG_LIB_H
#define MSG_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FALSE
#define FALSE  (0)
#endif

#ifndef TRUE
#define TRUE   (! FALSE)
#endif

#define byte char

#define MSG_MAX_LEN    (4096)
#define MSG_STR_LEN    (4072)

#define MSG_INT_SIZE     (11)
#define MSG_LONG_SIZE    (11)
#define MSG_DBL_SIZE     (17)

#ifdef  __cplusplus
extern "C" {
#endif

void   msg_get(char *s);
void   msg_set(char *s);

void   msg_reset(void);

void   msg_put_int(int i);
int    msg_get_int(void);

void   msg_put_double(double d);
double msg_get_double(void);

void   msg_put_string(char *s_in);
void   msg_get_string(char *s_out);

char * msg_itoa(char *s, int i);
char * msg_ftoa(char *s, float f);
char * msg_dtoa(char *s, double d);

#ifdef  __cplusplus
}
#endif

#endif /* NEW_RPC_H */

