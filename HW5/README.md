### CS553 Cloud Computing Homework 5 Repo
**Illinois Institute of Technology**  

**Team Name**: YZ-MSQ-BT
**Students**:  
* Yun Zi (yzi1@hawk.iit.edu)
* Bhavesh Rajesh Talreja (btalreja@hawk.iit.edu)
* Muhammad Sheheryar Qureshi (mqureshi6@hawk.iit.edu) 

## How to check and test your implementation

You can run all the checks and tests for your implementation by calling:
```
$ bash run-mysort.sh
```
## Flow
1. gensort to create test data, to see screenshots
2. Externel Sort
    1. Memory limit: 4Gb(Because the test laptop memory is just 7.47Gb(8G RAM), and program also have to use 1GB, so I choice 4GB to do internel sort).
    2. Multi-thread pools, I create a multi-thread pools can run 8 threads(throughing parameter, can use 1,2,4,16), but in my laptop, 8 thread is better than other choice.
    3. We read the data, and split them, and use qsort() to sort the data in memory, and write to temporary file.
        if the 16G file sort. 8 threads, we use:
            long frsize = MAX_MEMMORY / numThreads; // the size of each thread will read per time - 0.5GB
            int count = fsize / frsize == 0 ? 1: ceil(fsize / frsize); // the number of read time - 32 temproary files
        sort algo: quicksort, because if use merge sort, we have to use extra space.

    4. k-way merge sort, each time read one line from all of the temproary files. and pick up minimize line, write to output file.
        then choose the next line on minimize line file.

3. test
    linux test: time sort -k 1 16GB.txt -o 16GB-sort.txt --parallel=8
    mysort test: ./mysort 16GB.txt out.txt 8 >> mysort16GB.log
    results: mysortXX.log, linsortXX.log

4. Other optimize performance methods:
    1. k-way merge can be use multi-thread tech: 32 file -> 4 file -> 1 file (we have to test multi times external read/write performance)
    2. qsort() can be implemented by mannul, right now is using C library
    3. k-way merge can use min Heap to optimize the performance, rather than pick up the minimize line.
    4. Improve the top of limitation of memory(8GB), my laptop just can use 4GB.
