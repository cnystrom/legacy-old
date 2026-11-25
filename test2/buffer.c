/******************************************************************************
 *
 *    buffer.c
 *
 *    Copyright (C) 2005  <Chris Nystrom>
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
 *    E-Mail: cnystrom@gmail.com
 *    Blog:   http://conversazione.blogspot.com
 *    AIM:    nystromchris
 *
 *    Soli Deo Gloria
 *
 */

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include "types.h"
#include "buffer.h"

#define ERR1 "buffer overflow"

static byte buf[BUF_SIZE] = {0};
static int  buf_write_index;
static int  buf_read_index;

void
reset_buf(void)
{
  buf_read_index = 0;
  buf_write_index = 0;
}

byte *
get_buf(void)
{
  return(buf);
}

int
get_buf_index(void)
{
  return(buf_write_index);
}

void
set_buf_index(int i)
{
  buf_write_index = i;
}

void
display_buf(void)
{
  int i;

  for (i = 0; i < buf_write_index; i++) {
    printf("buf[%d] = %d\n", i, buf[i]);
  }
}

void
pack_int8(int8 int8)
{
  if ((buf_write_index + INT8_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int8(): %s\n", ERR1);
    return;
  }

  buf[buf_write_index++] = int8;
}

int8
unpack_int8(void)
{
  if ((buf_read_index + INT8_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int8(): %s\n", ERR1);
    return(-1);
  }

  return(buf[buf_read_index++]);
}

void
pack_int16(int16 i1)
{
  int   i;
  byte *bp;
  int16 i2;

//  printf("pack_int16(): buf_write_index = %d\n", buf_write_index);
//  printf("pack_int16(): buf_read_index = %d\n", buf_write_index);

  if ((buf_write_index + INT16_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int16(): %s\n", ERR1);
    return;
  }

  i2 = htons(i1);

  bp = (byte *) &i2;

  for (i = 0; i < INT16_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

int16
unpack_int16(void)
{
  int i;
  byte *bp;
  int16 i1;

//  printf("unpack_int16(): buf_write_index = %d\n", buf_write_index);
//  printf("unpack_int16(): buf_read_index = %d\n", buf_write_index);

  if ((buf_read_index + INT16_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int16(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &i1;

  for (i = 0; i < INT16_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

//  printf("unpack_int16(): int16 = %d\n", int16);

  return(ntohs(i1));
}

void
pack_int32(int32 i1)
{
  int   i;
  byte *bp;
  int32 i2;

//  printf("pack_int32(): buf_write_index = %d\n", buf_write_index);
//  printf("pack_int32(): buf_read_index = %d\n", buf_write_index);

  if ((buf_write_index + INT32_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_int32(): %s\n", ERR1);
    return;
  }

  i2 = htonl(i1);

  bp = (byte *) &i2;

  for (i = 0; i < INT32_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

int32
unpack_int32(void)
{
  int i;
  byte *bp;
  int32 i1;

//  printf("unpack_int32(): buf_write_index = %d\n", buf_write_index);
//  printf("unpack_int32(): buf_read_index = %d\n", buf_write_index);

  if ((buf_read_index + INT32_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_int32(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &i1;

  for (i = 0; i < INT32_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return(ntohl(i1));
}

/*
void
pack_float(float f)
{
  int   i;
  byte *bp;

  if ((buf_write_index + FLT_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_float(): %s\n", ERR1);
    return;
  }

  bp = (byte *) &f;

  for (i = 0; i < FLT_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

float
unpack_float(void)
{
  int i;
  byte *bp;
  float f;

  if ((buf_read_index + FLT_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_float(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &f;

  for (i = 0; i < FLT_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return(f);
}

void
pack_double(double d)
{
  int   i;
  byte *bp;

  if ((buf_write_index + DBL_SIZE) >= BUF_SIZE) {
    fprintf(stderr, "pack_double(): %s\n", ERR1);
    return;
  }

  bp = (byte *) &d;

  for (i = 0; i < DBL_SIZE; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

double
unpack_double(void)
{
  int i;
  byte *bp;
  double d;

  if ((buf_read_index + DBL_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_double(): %s\n", ERR1);
    return(-1);
  }

  bp = (byte *) &d;

  for (i = 0; i < DBL_SIZE; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return(d);
}
*/

void
pack_string(char *s)
{
  int   i;
  Uint16 len;
  byte *bp;

  len = strlen(s);

//  printf("pack_string(): len = %d\n", len);

  if ((buf_write_index + INT16_SIZE + len) >= BUF_SIZE) {
    fprintf(stderr, "pack_string(): %s\n", ERR1);
    return;
  }

  pack_int16(len);

  bp = (byte *) s;

  for (i = 0; i < len; i++) {
     buf[buf_write_index++] = *(bp++);
  }
}

void
unpack_string(char *s)
{
  int i;
  Uint16 len;
  byte *bp;

  if ((buf_read_index + INT16_SIZE) > buf_write_index) {
    fprintf(stderr, "unpack_string(): %s\n", ERR1);
    return;
  }

  len = unpack_int16();

//  printf("unpack_string(): len = %d\n", len);

  if ((buf_read_index + len) > buf_write_index) {
    fprintf(stderr, "unpack_string(): %s\n", ERR1);
    return;
  }

  bp = (byte *) s;

//  printf("unpack_string(): buf_read_index = %d\n", buf_read_index);

  for (i = 0; i < len; i++) {
    *(bp++) = buf[buf_read_index++];
  }

  return;
}

/*
void
display_string(char *s)
{
  int i, len;
  byte *bp;

  bp = (byte *) s;

  len = strlen(s);

//  printf("display_string(): len = %d\n", len);

  for (i = 0; i < len; i++) {
    printf("%d = %d\n", i, *(bp + i));
  }
}
*/
/*
int
main(void)
{
  int8 v1 = CHAR_MAX;
  int8 v2 = 0;
  int16 w1 = SHRT_MAX;
  int16 w2 = 0;
  int32 x1 = INT_MAX;
  int32 x2 = 0;
  char s1[] = "Test";
  char s2[20] = "";

  printf("\nv1 = %d\n", v1);
  printf("v2 = %d\n", v2);
  printf("w1 = %d\n", w1);
  printf("w2 = %d\n", w2);
  printf("x1 = %d\n", x1);
  printf("x2 = %d\n", x2);
  printf("s1 = |%s|\n", s1);
  printf("s2 = |%s|\n", s2);

  buf_write_index = 0;

  pack_int8(v1);
  pack_int16(w1);
  pack_int32(x1);
  pack_string(s1);

//  display_buf();

  buf_read_index = 0;

  v2 = unpack_int8();
  w2 = unpack_int16();
  x2 = unpack_int32();
  unpack_string(s2);

  printf("\nv1 = %d\n", v1);
  printf("v2 = %d\n", v2);
  printf("w1 = %d\n", w1);
  printf("w2 = %d\n", w2);
  printf("x1 = %d\n", x1);
  printf("x2 = %d\n", x2);
  printf("s1 = |%s|\n", s1);
  printf("s2 = |%s|\n\n", s2);

  exit(0);
}
*/

