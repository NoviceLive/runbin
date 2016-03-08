/*
Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>

This file is part of RunBin.

RunBin is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RunBin is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RunBin.  If not, see <http://www.gnu.org/licenses/>.
*/


# ifndef _GU_ZHENGXIONG_LIBHEX_H
# define _GU_ZHENGXIONG_LIBHEX_H


void
print_hex(char *string);

char *
unhex(char *string);


/* The following functions are kept here just for convenience. */


void
print_mem(void *addr, size_t count);

int
make_exec(void *addr, size_t count);

void
exec_addr(void *addr);

char *
remove_chars(char *input, char * evil);


# endif /* libhex.h */
