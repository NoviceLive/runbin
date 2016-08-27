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


# ifndef CPP
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>

# ifdef __linux__
#  include <sys/mman.h> /* For mprotect. */
# endif /* __linux__ */
# ifdef _WIN32
#  include <windows.h> /* For VirtualProtect. */
# endif /* _WIN32 */
# endif

# include "libhex.h"


void
print_hex(char *string)
{
    size_t i;
    for (i = 0; i < strlen(string); ++i)
        printf("%x", (unsigned int)string[i]);

    (void)putchar('\n');
}


char *
unhex(char *string)
{
    char temp[3];
    size_t i;
    size_t length = strlen(string);
    for (i = 0; i < length; i += 2) {
        strncpy(temp, string + i, 2);
        string[i / 2] = (char)strtoul(temp, NULL, 16);
    }
    string[i / 2] = (char)0;
    return string;
}


void
print_mem(void *addr, size_t count)
{
    for (size_t current = 0; current < count; current += 1) {
        if (current && current % 16 == 0) {
            putchar('\n');
        }
        printf("%02x ", *((unsigned char *)addr + current));
    }
    putchar('\n');
}


int
make_exec(void *addr, size_t count)
{
# ifdef __linux__
    int failure = mprotect ((void *)((uintptr_t)addr & ~4095),
                            count,
                            PROT_READ | PROT_WRITE | PROT_EXEC);
    return failure ? 0 : 1;
# endif /* __linux__ */

# ifdef _WIN32
    DWORD why_must_this_variable;
    BOOL success = VirtualProtect (addr, count,
                                   PAGE_EXECUTE_READWRITE,
                                   &why_must_this_variable);
    return success ? 1 : 0;
# endif /* _WIN32 */
}


void
exec_addr(void *addr)
{
    ((void (*)(void))addr)();
}


char *
remove_chars(char *input, char * evil)
{
    size_t evil_len = strlen(evil);
    for (size_t round = 0; round < evil_len; round += 1) {
        size_t input_len = strlen(input);
        size_t good = 0;
        for (size_t current = 0; current < input_len; current += 1) {
            if (input[current] == evil[round]) {
                continue;
            } else {
                input[good] = input[current];
                good += 1;
            }
        }
        input[good] = '\0';
    }
    return input;
}
