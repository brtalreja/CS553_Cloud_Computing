./cpubench 20 single 1000 4 true >> job-result.md
./cpubench 20 single 4000 4 true >> job-result.md
./cpubench 20 double 1000 4 true >> job-result.md
./cpubench 20 double 4000 4 true >> job-result.md

./cpubench 20 single 1000 -1 true >> job-result.md
./cpubench 20 single 4000 -1 true >> job-result.md
./cpubench 20 double 1000 -1 true >> job-result.md
./cpubench 20 double 4000 -1 true >> job-result.md

./cpubench 20 single 16000 -1 true >> job-result.md
./cpubench 20 double 16000 -1 true >> job-result.md

./cpubench 20 single 16000 4 true >> job-result.md
./cpubench 20 double 16000 4 true >> job-result.md