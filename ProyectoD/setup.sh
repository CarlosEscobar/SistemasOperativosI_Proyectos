nasm bootload.asm
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

as86 kernel.asm -o kernel_asm.o

bcc -ansi -c -o tshell.o tshell.c
ld86 -o tshell -d tshell.o kernel_asm.o