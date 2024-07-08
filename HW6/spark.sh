# git clone
git clone https://github.com/datasys-classrooms/cs553-fall2022-hw6-yz-msq-bt.git /exports/projects/cs553-fall2022-hw6-yz-msq-bt

# go to spark lib dir
cd /exports/projects/spark-3.0.0-preview2-bin-hadoop3.2

# mv file to spark dir
cp /exports/projects/cs553-fall2022-hw6-yz-msq-bt/SparkSort.java SparkSort.java

# compile spark file
javac -cp jars/spark-core_2.12-3.0.0-preview2.jar:jars/scala-library-2.12.10.jar:jars/log4j-1.2.17.jar  SparkSort.java
jar cvf SparkSort.jar SparkSort.class

# test data for 3GB
/exports/projects/hadoop-3.2.3/bin/hadoop fs -put /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-3GB /home/input/data-3GB
bin/spark-submit --class SparkSort --master yarn --deploy-mode cluster --driver-memory 6G --executor-memory 6G --executor-cores 4 --num-executors 80 --conf "spark.default.parallelism=250" SparkSort.jar /home/input/data-3GB /home/output/data-3GB-spark
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/input/data-3GB 
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/output/data-3GB-spark 

# test data for 6GB
/exports/projects/hadoop-3.2.3/bin/hadoop fs -put /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-6GB /home/input/data-6GB
bin/spark-submit --class SparkSort --master yarn --deploy-mode cluster --driver-memory 4G --executor-memory 4G --executor-cores 4 --num-executors 50 --conf "spark.default.parallelism=250" SparkSort.jar /home/input/data-6GB /home/output/data-6GB-spark
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/input/data-6GB 
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/output/data-6GB-spark 

# test data for 12GB
/exports/projects/hadoop-3.2.3/bin/hadoop fs -put /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-12GB /home/input/data-12GB
bin/spark-submit --class SparkSort --master yarn --deploy-mode cluster --driver-memory 4G --executor-memory 4G --executor-cores 4 --num-executors 50 --conf "spark.default.parallelism=250" SparkSort.jar /home/input/data-12GB /home/output/data-12GB-spark
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/input/data-12GB 
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/output/data-12GB-spark 

# test data for 24GB
/exports/projects/hadoop-3.2.3/bin/hadoop fs -put /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-24GB /home/input/data-24GB
bin/spark-submit --class SparkSort --master yarn --deploy-mode cluster --driver-memory 4G --executor-memory 4G --executor-cores 4 --num-executors 50 --conf "spark.default.parallelism=250" SparkSort.jar /home/input/data-24GB /home/output/data-24GB-spark
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/input/data-24GB 
/exports/projects/hadoop-3.2.3/bin/hadoop fs -rm -r -f /home/output/data-24GB-spark 


# Cluster nodes have 16 CPU cores, 32GB RAM, and 4 disks
# Reserved Memory = 6GB
# Min Container size = 2GB

# Containers = minimum of (2 * 16, 1.8 * 4, (32-8)/4) = 6
# RAM per container = maximum of (2, (32-8)/6) = 4GB

# yarn.nodemanager.resource.memory-mb = 6 * 4 * 1024
