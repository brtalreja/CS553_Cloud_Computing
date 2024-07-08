CC=gcc
CFLAGS=-Wall -pthread -mavx -O3 -mfma

build: cpubench

test: cpubench
	bash runbench.sh

cpubench: cpubench.c
	$(CC) $(CFLAGS) -o cpubench $<

clean:
	rm -rf cpubench

# set args 0 matrix single 4 1 true