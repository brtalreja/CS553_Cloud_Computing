# CS553 Cloud Computing Homework 1
**Illinois Institute of Technology**  
Student: Bhavesh Rajesh Talreja (btalreja@hawk.iit.edu)

## How to run the programs 
The instructions to run the programs are mentioned in the following sections.

### Program 1 : generate-dataset.sh

For this, I used SRANDOM variable of linux and Password gen function to generate the 32-bit integer and ASCII string of 100 bytes respectively.
Using two command line arguments, we generate the file using the text and the number value to generate the number of records.

To run: time bash generate-dataset.sh argument1 argument2
Where argument1 will be the text that will become the filename and argument2 will be a number that will be the number of records in the file. We use the time command to get the time of execution.

### Program 2 : sort-data.sh

For this, I used sort command of linux and -k to sort the data using a key and the command line option 1n to sort the data based on 1st column which is a number.
Using two command line arguments, we generate the sorted file.

To run: time bash sort-data.sh argument1 argument2
Where argument1 will be the text that will open the input file and argument2 will be a text that will be the output file name. We use the time command to get the time of execution.

### Program 3 : plot.py

For this, I generated and sorted 3 data sets as per the instruction in the question. I created a function to convert the time data into milli seconds. I used the log function to bring down the different scales to a logarithmic scale. We use the matplotlib library to plots the final plots of Time to generate records vs. Number of records and Time to sort records vs. Number of records.

To run: python3 plot.py
Where the output shows two output windows of the two plots aforementioned.

