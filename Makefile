CROSS_COMPILE	:=
CC	:= $(CROSS_COMPILE)gcc -c
INCLUDE	:= -I"$(PWD)/include"
CAPPEND	:= -m32
CFLAGS	:= $(CAPPEND) -nostdinc -nostdlib -ffreestanding $(INCLUDE)
SRCS = $(shell find -name '*.[cS]')
OBJS = $(addsuffix .o,$(basename $(SRCS)))



all: $(OBJS)
	echo "done."

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	cd src; rm *.o
