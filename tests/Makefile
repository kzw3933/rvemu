SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %, $(SRCS))
CC = /home/jack/.riscv/riscv64-elf-ubuntu-20.04-nightly-2023.03.14-nightly/riscv/bin/riscv64-unknown-elf-gcc

.PHONY: all

all:$(OBJS)


$(OBJS): %: %.c
	$(CC) -o $@ $^

