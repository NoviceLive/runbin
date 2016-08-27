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
# endif

# include "libhex.h"


int
main(int argc, char **argv)
{
    if (argc != 2) {
        printf("%s\n", "Invalied Argument!");
        return EXIT_FAILURE;
    }

    print_hex(argv[1]);

    return EXIT_SUCCESS;
}
