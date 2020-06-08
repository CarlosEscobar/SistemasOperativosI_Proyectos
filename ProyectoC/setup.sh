nasm bootload.asm
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

bcc -ansi -c -o tprog1.o tprog1.c
as86 kernel.asm -o kernel_asm.o
ld86 -o tprog1 -d tprog1.o kernel_asm.o
