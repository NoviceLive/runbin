RunBin
======


Execute data on the stack (used for the time being).


Installation
------------

From Binary
+++++++++++

Prebuilt binaries exist for both Linux and Windows.

From Source
+++++++++++

Requirements
************

- `Cofyc/argparse <https://github.com/Cofyc/argparse>`_ MIT

  It was added as RunBin's submodule.

Build Dependencies
******************

- `SCons <http://scons.org/>`_

  Alternatively, you can also manually compile RunBin without trouble.


Usage
-----

::

   runbin --help
   Usage: runbin [-e] [-q] <filename>

       -h, --help        show this help message and exit
       -e, --escape      Use escape or raw hex.
       -q, --quiet       Don't confirm.
       -V, --version     Show the version and exit.


Examples
++++++++

::

   $ hexdump tests/64.bin
   0000000 f631 bb48 622f 6e69 2f2f 6873 5356 5f54
   0000010 3b6a 3158 0fd2 0005
   0000017
   $ runbin tests/64.bin

   $ less -FX tests/64.esc
   \x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05
   $ runbin tests/64.esc -e

   $ less -FX tests/64.txt
   31f648bb2f62696e2f2f73685653545f6a3b5831d20f05
   $ runbin tests/64.txt -e


Other Utilities
---------------

- ``disbin32``

  Disassemble the given raw binary using ``objdump``.

  A shorthand for the following. (Since our memory sucks.)

  ::

     objdump -D -b binary -m i386 -M intel "${filename}" | less -FXR

- ``disbin64``

  Disassemble the given raw binary using ``objdump``.

  A shorthand for the following. (Since our memory sucks.)

  ::

     objdump -D -b binary -m i386:x86-64 -M intel "${filename}" | less -FXR

- ``hex``

  ::

     hex 4567
     34353637

- ``unhex``

  ::

     unhex 4567
     Eg


Caveats
+++++++

pwntools_ also provide these two commands,
i.e. ``hex`` and ``unhex``, which are, however, slow.

Presumably, time consumed for the OS to load Python outweighs
that needed for Python to accomplish the task.


Libraries
---------

- Hexadecimal

  - print_hex

  - unhex

- Memory

  - print_mem

  - make_exec

  - exec_addr

- String

  - remove_chars


.. _pwntools: https://github.com/Gallopsled/pwntools
