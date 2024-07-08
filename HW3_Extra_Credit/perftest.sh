# use 4 thread to test oneapi implementation of matrix multiplication
./cpubench 20 single 1000 4 true
./cpubench 20 single 4000 4 true
./cpubench 20 single 16000 4 true
./cpubench 20 double 1000 4 true
./cpubench 20 double 4000 4 true
./cpubench 20 double 16000 4 true
# use bigest hardware thread to test oneapi implementation of matrix multiplication
./cpubench 20 single 1000 -1 true
./cpubench 20 single 4000 -1 true
./cpubench 20 single 16000 -1 true
./cpubench 20 double 1000 -1 true
./cpubench 20 double 4000 -1 true
./cpubench 20 double 16000 -1 true