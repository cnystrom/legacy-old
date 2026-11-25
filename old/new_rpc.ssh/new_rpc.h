/*
 *    new_rpc.h
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
 *    E-Mail: ccn@olenska.hn.org or nystrom@cactus.org
 *
 *    Soli Deo Gloria
 *
 */

#ifndef NEW_RPC_H
#define NEW_RPC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "msg_lib.h"

#define NRPC_EXIT         (-1)
#define NRPC_REVERSE      (-2)
#define NRPC_INVALID      (-3)
#define NRPC_FAILED       (-4)

#ifdef  __cplusplus
extern "C" {
#endif

void nrpc_init_server(void);
void nrpc_welcome(char *str);

int  nrpc_init_client(char *username, char *hostname, char *command,
       char *passwd);
void nrpc_send_message(void);
void nrpc_send_response(void);
void nrpc_reverse(void);
void nrpc_exit(void);
void nrpc_close(void);

void nrpc_set_function(int func_num);
int  nrpc_get_function(void);
void nrpc_std_response(void);
void nrpc_wait_for_reverse(void);

int  nrpc_read_more(void);

#ifdef  __cplusplus
}
#endif

#endif /* NEW_RPC_H */

