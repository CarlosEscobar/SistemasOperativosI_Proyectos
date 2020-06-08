nasm bootload.asm
dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
