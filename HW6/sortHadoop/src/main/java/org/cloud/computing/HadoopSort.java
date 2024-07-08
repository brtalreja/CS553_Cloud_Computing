import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.lib.InputSampler;
import org.apache.hadoop.mapred.lib.TotalOrderPartitioner;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.Partitioner;
import org.apache.log4j.Logger;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class HadoopSort {

  private static final Logger logger = Logger.getLogger(HadoopSort.class);

  public static class TokenizerMapper
       extends Mapper<Object, Text, Text, Text>{

    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
      context.write(new Text(value.toString().substring(0)), new Text(""));
    }
  }

  public static class IntSumReducer
       extends Reducer<Text,Text,Text, Text> {
    public void reduce(Text key, Iterable<Text> values,
                       Context context
                       ) throws IOException, InterruptedException {
        for (Text v : values) {
          context.write(key, v);
        }
    }
  }

  public static void main(String[] args) throws Exception {
    logger.info("Start ===============================================================================");
    long start = System.currentTimeMillis();
    Configuration conf = new Configuration();
    Job job = Job.getInstance(conf, "hadoop sort");
    job.setJarByClass(HadoopSort.class);
    job.setMapperClass(TokenizerMapper.class);
    job.setCombinerClass(IntSumReducer.class);

    job.setNumReduceTasks(1);
    job.setPartitionerClass(TotalOrderPartitioner.class);
    FileInputFormat.setInputPaths(job, new Path(args[0]));
    TotalOrderPartitioner.setPartitionFile(job.getConfiguration(), new Path(args[2]));
    InputSampler.writePartitionFile(job, new InputSampler.RandomSampler<Text, Text>(0.01, 10000));
    

    job.setReducerClass(IntSumReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(Text.class);
    
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    job.waitForCompletion(true);
    long timeElapsed = System.currentTimeMillis() - start;
    logger.info("Time elapsed in ms : ");
    logger.info(timeElapsed);
    logger.warn("End ===============================================================================");
    System.exit(0);
  }
}