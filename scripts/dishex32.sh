#!/usr/bin/env zsh


#
# Copyright 2015-2016 Gu Zhengxiong <rectigu@gmail.com>
#


if [[ $# -ne 1 ]]; then
    printf '%s\n' 'Required argument: hex to be disassembled!'
    exit 1
fi


objdump -D -b binary -m i386 -M intel =(unhex "${1}") | less -FXR
