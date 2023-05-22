nasm -f elf64 ./src/hash.s -o ./obj/hash.o
ld -s -o hash ./obj/hash.o
# ./hash