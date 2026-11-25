/*
 *    file_xfr.c
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

#include "file_xfr.h"

static char server[256];
static char app_name[256];
static char app_ver[256];
static char niodir[256];
static char dirname[256];
static char cwd[256];

static char filepath[256];

void
init_file_loader(char *s, char *an, char *av, char *dir)
{
  get_homedir(niodir);
  strncat(niodir, "/.nio/cache", 11);

  strcpy(server, s);
  strcpy(app_name, an);
  strcpy(app_ver, av);

  strcpy(dirname, niodir);
  strcat(dirname, server);
  strcat(dirname, "/");
   
  strcat(dirname, app_name);
  strcat(dirname, "/");

  strcat(dirname, app_ver);
  strcat(dirname, "/");

  strcpy(cwd, dir);

  /*
  printf("dirname: ");
  printf(dirname);
  printf("\n");


  printf("cwd: ");
  printf(cwd);
  printf("\n");

  fflush(stdout);
  */
}

char *
load_file(char *filename)
{
  char command[256];

//  printf("load_file(): filename = %s\n", filename);

  strcpy(dirname, niodir);
  strcat(dirname, server);
  strcat(dirname, "/");
 
  check_dir(dirname);

  strcat(dirname, app_name);
  strcat(dirname, "/");

  check_dir(dirname);

  strcat(dirname, app_ver);
  strcat(dirname, "/");

  check_dir(dirname);

  strcpy(filepath, dirname);
  strcat(filepath, basename(filename));

//  strcpy(command, "rcp ");
  strcpy(command, "cp ");
//  strcat(command, server);
//  strcat(command, ":");
  strcat(command, cwd);
  strcat(command, "/");
  strcat(command, filename);
  strcat(command, " ");
  strcat(command, filepath);
  strcat(command, " &");

//  printf("load_file(): command = %s\n", command);

  system(command);

//  printf("file_index = %d\n", file_index);

  return(filepath);
}

/*
char *
get_file_path(int index)
{
  if (index >= 0 && index < file_index)
  {
    printf("index = %d\n", index);
    printf("file_list[index] = ");
    printf(file_list[index]);
    printf("\n");

    return(file_list[index]);
  }
  else
  {
    printf("get_file_path: bad index value %d\n", index);
    return(NULL);
  }
}
*/

