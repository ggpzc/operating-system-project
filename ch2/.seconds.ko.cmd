cmd_/home/pzc/os/ch2/seconds.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/pzc/os/ch2/seconds.ko /home/pzc/os/ch2/seconds.o /home/pzc/os/ch2/seconds.mod.o ;  true
