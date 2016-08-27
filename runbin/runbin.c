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

# include <argparse.h>
# endif

# ifdef __linux__
# define SIZE_T_FMT "%zu"
# endif /* __linux__ */
# ifdef _WIN32
# define SIZE_T_FMT "%Iu"
# endif /* _WIN32 */

# include "libhex.h"


# define SIZE 8192


int
main (int argc, const char * argv[])
{
    int escape = 0;
    int quiet = 0;
    int version = 0;

    struct argparse argparse;
    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_BOOLEAN('e', "escape", &escape, "Use escape or raw hex."),
        OPT_BOOLEAN('q', "quiet", &quiet, "Don't confirm."),
        OPT_BOOLEAN('V', "version", &version,
                    "Show the version and exit."),
        OPT_END()
    };
    static const char *const usage[] = {
        "runbin [-e] [-q] <filename>", NULL
    };
    argparse_init(&argparse, options, usage, 0);
    argc = argparse_parse(&argparse, argc, argv);

    if (version) {
        printf("%s\n", "RunBin, version 0.1.0");
        return EXIT_SUCCESS;
    }
    if (!argc) {
        fprintf(stderr, "[x] %s\n", "Wrong arguments!");
        return EXIT_FAILURE;
    }

    char buffer[SIZE];
    const char *filename = argv[0];
    FILE *stream = fopen(filename, "rb");
    if (stream == NULL) {
        fprintf(stderr, "[x] Error opening file: %s\n", filename);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Opened: %s\n", filename);
    size_t count = fread(buffer, 1, SIZE, stream);
    if (ferror(stream)) {
        fprintf(stderr, "[x] Error reading file: %s\n", filename);
        fclose(stream);
        return EXIT_FAILURE;
    }
    fprintf(stderr, "Read: %s\n", filename);
    fclose(stream);
    fprintf(stderr, "Closed: %s\n", filename);

    void *addr = NULL;
    if (escape) {
        fprintf(stderr, "%s\n", "Unescaping...");
        remove_chars(buffer, "\\x\n");
        unhex(buffer);
        count = strlen(buffer);
        addr = buffer;
        fprintf(stderr, "%s\n", "Unescaped.");
    } else {
        addr = buffer;
    }

    size_t display_count = count > 4096 ? 4096 : count;
    fprintf(stderr, "[-] Printing memory: %p %d %d\n",
            addr, count, display_count);
    print_mem(addr, display_count);

    if (!quiet) {
        fprintf(stderr, "Testing shellcode might be dangerous.\n");
        fprintf(stderr, "Are you sure? Enter to continue...");
        getchar();
    }

    if (make_exec(addr, count)) {
        fprintf(stderr, "[-] Executing address: %p\n", addr);
        exec_addr(addr);
    } else {
        fprintf(stderr, "[x] Error Making Exec: %p\n", addr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
