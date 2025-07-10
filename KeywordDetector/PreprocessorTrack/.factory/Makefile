#
# sampler
# 
# File created : 2025-06-02
#

CC                ?= gcc
CFLAGS            += -O3 -Wall -lm -Wno-unused-function
EXTRA_RUNNER_ARGS := --verbose

all: convert

# The C executable is the linked object files
sampler: sampler.o runner.o 
	$(CC) -o $@ $^ $(CFLAGS)
	
# Object files are dependent on C files.
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) -include sampler.h

convert: sampler filelist.txt
	./sampler --output-has-duration -v --batch-write --batch filelist.txt $(EXTRA_RUNNER_ARGS)

.PHONY: all clean

clean:
	rm -f sampler sampler.exe runner.o sampler.o

