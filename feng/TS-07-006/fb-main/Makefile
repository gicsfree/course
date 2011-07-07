#
# Copyright (C) 2000-2008 China
# All rights reserved.
#
# Filename:Makefile 
#  -> Framebuffer
# 
# Authors: Guo Tongbin <guotongbin@gmail.com>
# Version: V0.0
# Create Time: 2010.03.05
# 
# Remarks: OS -> Linux(Ubuntu)
#          Compiler -> GNU Toolchain
#
src = $(wildcard *.c)
obj = $(patsubst %.c, $(DIR)%.o, $(src))
target = main
lib = libfb.a

CC = gcc
#CC = arm-linux-gcc
CFLAGS = -Wall -g -c -I../freetype-2.3.11/include
LDFLAGS = -lm -L../freetype-2.3.11/objs/.libs -lfreetype

all: $(target) lib

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:%.c
	$(CC) -o $@ $(CFLAGS) $< 

lib:fb.o
	ar -rs $(lib) $^

clean:
	-rm -f $(target)
	-rm -f $(obj)
	-rm -f *~
	-rm -f $(lib)

.PHONY: clean
