bash runbench.sh
Already up to date.
1. Check to see if the README is updated ...                                   passed!
2. Check to see if the report is uploaded ...                                  failed!
3. Check to see if the code is uploaded ...                                    passed!
4. Check to see if the runbench script is not modified ...                     passed!
5. Check to see if the code compiles ...                                       passed!
1. Test single precision 2000 flops with 1 thread                              passed!
*** Test 1 run log ***
./cpubench 28620 flops single 2000 1 false
seed=28620 mode=flops type=single size=2000 threads=1 time=0.000172 throughput=11627.906977 checksum=0
*** Run successful ***
2. Test single precision 2000 flops with 2 thread                              passed!
*** Test 2 run log ***
./cpubench 22403 flops single 2000 2 false
seed=22403 mode=flops type=single size=2000 threads=2 time=0.000108 throughput=18518.518519 checksum=0
*** Run successful ***
3. Test single precision 2000 flops with 4 thread                              passed!
*** Test 3 run log ***
./cpubench 10742 flops single 2000 4 false
seed=10742 mode=flops type=single size=2000 threads=4 time=0.000171 throughput=11695.906433 checksum=0
*** Run successful ***
4. Test single precision 2000 flops with 8 thread                              passed!
*** Test 4 run log ***
./cpubench 22403 flops single 2000 8 false
seed=22403 mode=flops type=single size=2000 threads=8 time=0.000168 throughput=11904.761905 checksum=0
*** Run successful ***
5. Test double precision 2000 flops with 1 thread                              passed!
*** Test 5 run log ***
./cpubench 28620 flops double 2000 1 false
seed=28620 mode=flops type=double size=2000 threads=1 time=0.000103 throughput=19417.475728 checksum=0
*** Run successful ***
6. Test double precision 2000 flops with 2 thread                              passed!
*** Test 6 run log ***
./cpubench 5054 flops double 2000 2 false
seed=5054 mode=flops type=double size=2000 threads=2 time=0.000100 throughput=20000.000000 checksum=0
*** Run successful ***
7. Test double precision 2000 flops with 4 thread                              passed!
*** Test 7 run log ***
./cpubench 12340 flops double 2000 4 false
seed=12340 mode=flops type=double size=2000 threads=4 time=0.000121 throughput=16528.925620 checksum=0
*** Run successful ***
8. Test double precision 2000 flops with 8 thread                              passed!
*** Test 8 run log ***
./cpubench 5054 flops double 2000 8 false
seed=5054 mode=flops type=double size=2000 threads=8 time=0.000158 throughput=12658.227848 checksum=0
*** Run successful ***
9. Test double precision 2000x2000 matrix multiplication with 1 thread         passed!
*** Test 9 run log ***
./cpubench 5865 matrix double 2000 1 false
num_threads: 1
seed=5865 mode=matrix type=double size=2000 threads=1 time=4.549456 throughput=-0.120766 checksum=465611805
*** Run successful ***
10. Test double precision 2000x2000 matrix multiplication with 2 thread       passed!
*** Test 10 run log ***
./cpubench 12340 matrix double 2000 2 false
num_threads: 2
seed=12340 mode=matrix type=double size=2000 threads=2 time=2.318431 throughput=-0.236979 checksum=-2105601733
*** Run successful ***
11. Test double precision 2000x2000 matrix multiplication with 4 threads      passed!
*** Test 11 run log ***
./cpubench 5865 matrix double 2000 4 false
num_threads: 4
seed=5865 mode=matrix type=double size=2000 threads=4 time=1.265505 throughput=-0.434150 checksum=465611805
*** Run successful ***
12. Test double precision 2000x2000 matrix multiplication with 8 threads      passed!
*** Test 12 run log ***
./cpubench 10742 matrix double 2000 8 false
num_threads: 8
seed=10742 mode=matrix type=double size=2000 threads=8 time=1.298929 throughput=-0.422979 checksum=2115055341
*** Run successful ***
