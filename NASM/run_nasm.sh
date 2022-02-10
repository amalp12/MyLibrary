# replace  /usr/bin/bash with path to your bash
# it can be found by typing which bash in the terminal
#! /usr/bin/bash

read -p "Enter the path to your NASM File : " PATH

# replace /usr/bin/nasm with the path to your nasm executable
# it can be found by typing which nasm in the terminal
/usr/bin/nasm -f elf32 ${PATH}.asm -o ${PATH}.o

# replace /usr/bin/ld with the path to your ld executable
# it can be found by typing which ld in the terminal
/usr/bin/ld -m elf_i386 ${PATH}.o -o ${PATH}

./${PATH}

exit
