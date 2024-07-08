import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.log4j.Logger;
import scala.Tuple2;
import java.util.Arrays;
public class SparkSort {

		private static final Logger logger = Logger.getLogger(SparkSort.class);
        public static void main(String[] args) {
			logger.info("Start Spark: ===============================================================================");
			long start = System.currentTimeMillis();
			SparkConf sparkConf = new SparkConf().setAppName("Spark Sort");
			JavaSparkContext sparkContext = new JavaSparkContext(sparkConf);
			String in = args[0];
			String out = args[1];
			JavaRDD<String> textFile = sparkContext.textFile(in);
			// one line get a key, for key to sort
			JavaPairRDD<String, String> counts = textFile
					.mapToPair(word -> new Tuple2<>(word.substring(0, 98), "")).sortByKey(true);
			// map to one file
			counts.map(x -> x._1 + "\t" + x._2).repartition(1).saveAsTextFile(out);
			sparkContext.close();
			long diff = System.currentTimeMillis() - start;
			logger.info("spark time diff in ms : \n");
			logger.info(diff);
			logger.info("End Spark: ===============================================================================");
        }
}