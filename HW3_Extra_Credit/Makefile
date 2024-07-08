CC=icpx
CFLAGS=-fsycl 

build: cpubench

test: cpubench
	bash runbench.sh

cpubench: cpubench.cpp
	$(CC) $(CFLAGS) $< -o cpubench

clean:
	rm -rf cpubench

env:
	source /opt/intel/oneapi/setvars.sh
	
#  source /opt/intel/oneapi/setvars.sh
# icpx -fsycl ./matrix.cpp -o ./matrix