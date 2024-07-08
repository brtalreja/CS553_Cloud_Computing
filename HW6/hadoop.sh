# !bin/bash

Project=/exports/projects/cs553-fall2022-hw6-yz-msq-bt
HadoopPath=/exports/projects/hadoop-3.2.3

# git clone
git clone https://github.com/datasys-classrooms/cs553-fall2022-hw6-yz-msq-bt.git ${Project}/
cd ${Project}/ && git pull

# mv file to hadoop dir
cp ${Project}/HadoopSort.java ${HadoopPath}/HadoopSort.java

# go to hadoop lib dir
cd ${HadoopPath}

# compile hadoop file
export HADOOP_CLASSPATH=$(bin/hadoop classpath)
javac -classpath ${HADOOP_CLASSPATH} -d HadoopSort/ HadoopSort.java
jar -cvf HadoopSort.jar -C HadoopSort/ .

# after gensort
# bash ./gensort.sh
# test data for 3GB
${Project}/Scripts/gensort -a -b0 -t8 30000000 ${Project}/data/data-3GB
bin/hadoop fs -put ${Project}/data/data-3GB /home/input/data-3GB
bin/hadoop jar HadoopSort.jar HadoopSort /home/input/data-3GB /home/output/data-3GB /home/partition/data-3GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/input/data-3GB 
${HadoopPath}/bin/hadoop fs -rm -r -f /home/output/data-3GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/partition/data-3GB 
rm -rf ${Project}/data/data-3GB

# test data for 6GB
${Project}/Scripts/gensort -a -b0 -t8 60000000 ${Project}/data/data-6GB
bin/hadoop fs -put ${Project}/data/data-6GB /home/input/data-6GB
bin/hadoop jar HadoopSort.jar HadoopSort /home/input/data-6GB /home/output/data-6GB /home/partition/data-6GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/input/data-6GB 
${HadoopPath}/bin/hadoop fs -rm -r -f /home/output/data-6GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/partition/data-6GB 
rm -rf ${Project}/data/data-6GB

# test data for 12GB
${Project}/Scripts/gensort -a -b0 -t8 120000000 ${Project}/data/data-12GB
bin/hadoop fs -put ${Project}/data/data-12GB /home/input/data-12GB
bin/hadoop jar HadoopSort.jar HadoopSort /home/input/data-12GB /home/output/data-12GB /home/partition/data-12GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/input/data-12GB 
${HadoopPath}/bin/hadoop fs -rm -r -f /home/output/data-12GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/partition/data-12GB 
rm -rf ${Project}/data/data-12GB

# test data for 24GB
${Project}/Scripts/gensort -a -b0 -t8 240000000 ${Project}/data/data-24GB
bin/hadoop fs -put ${Project}/data/data-24GB /home/input/data-24GB
bin/hadoop jar HadoopSort.jar HadoopSort /home/input/data-24GB /home/output/data-24GB /home/partition/data-24GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/input/data-24GB 
${HadoopPath}/bin/hadoop fs -rm -r -f /home/output/data-24GB
${HadoopPath}/bin/hadoop fs -rm -r -f /home/partition/data-24GB 
rm -rf ${Project}/data/data-24GB