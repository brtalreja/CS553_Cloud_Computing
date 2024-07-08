# sort
time sort -k 1 1GB.txt -o 1GB-sort.txt --parallel=8
# sort
time sort -k 1 4GB.txt -o 4GB-sort.txt --parallel=8
# sort
time sort -k 1 16GB.txt -o 16GB-sort.txt --parallel=8
# sort
time sort -k 1 64GB.txt -o 64GB-sort.txt --parallel=8

rm -rf out.txt && ./mysort 1GB.txt out.txt 8 >> mysort1GB.log
rm -rf out.txt && ./mysort 4GB.txt out.txt 8 >> mysort4GB.log
rm -rf out.txt && ./mysort 16GB.txt out.txt 8 >> mysort16GB.log
rm -rf out.txt && ./mysort 64GB.txt out.txt 8 >> mysort64GB.log