cmd_/home/pzc/cse/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/pzc/cse/hello.ko /home/pzc/cse/hello.o /home/pzc/cse/hello.mod.o
