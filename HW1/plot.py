import sys
import matplotlib.pyplot as plt
import math
import re

USAGE="Usage: python3 plot.py"

time_converter=[60000,1000,1]

def conv_millisec(time_entry):
    time_entry_conv=re.sub(r"[a-z]",":",time_entry[:-1])
    return sum([x*int(float(y)) for x,y in zip(time_converter,time_entry_conv.split(":"))])

def main(args):
    print(USAGE)

    # TO-DO finish implementation
    num_entries = [1000,100000,10000000]

    num_entries_log=[math.log(value) for value in num_entries]

    gen_time=['00m01.127s','01m49.012s','198m28.162s']

    gen_time_log=[math.log(conv_millisec(value)) for value in gen_time]

    sort_time=['00m00.004s','00m01.797s','01m47.416s']

    sort_time_log=[math.log1p(conv_millisec(value)) for value in sort_time]

    fig, ax1 = plt.subplots()
    fig, ax2 = plt.subplots()

    ax1.set_xlabel('Number of Records (values in log)')
    ax1.set_ylabel('Time taken to generate records (values in log)')
    ax1.set_title('Time taken to generate records vs. Number of Records')
    ax1.scatter(num_entries_log,gen_time_log)
    ax2.set_xlabel('Number of Records (values in log)')
    ax2.set_ylabel('Time taken to sort records (values in log)')
    ax2.set_title('Time taken to sort records vs. Number of records')
    ax2.scatter(num_entries_log,sort_time_log)
    plt.show()


if __name__ == "__main__":
    main(sys.argv)
