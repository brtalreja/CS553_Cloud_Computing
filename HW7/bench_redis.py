import redis
import csv
import datetime

test_data = []
with open('test_data.csv', encoding='utf-8') as f:
     reader = csv.DictReader(f)
     for row in reader:
         test_data.append((row['key'], row['value']))

test_size = len(test_data)
print("test_data size:%d" % test_size)

r = redis.Redis(host='127.0.0.1')

total_start = datetime.datetime.now()

# insert
start = datetime.datetime.now()

for i in range(1000):
    r.set(test_data[i][0], test_data[i][1])

end = datetime.datetime.now()

inserttime = end - start
print("insert %d items time consumed: %sus" % (test_size, inserttime.microseconds) )

# lookup

start = datetime.datetime.now()

for i in range(1000):
    r.get(test_data[i][0])

end = datetime.datetime.now()

lookuptime = end - start
print("lookup %d items time consumed: %sus" % (test_size, lookuptime.microseconds) )

# delete

start = datetime.datetime.now()

for i in range(1000):
    r.delete(test_data[i][0])

end = datetime.datetime.now()

deletetime = end - start
print("delete %d items time consumed: %sus" % (test_size, deletetime.microseconds) )

# total
total_end = datetime.datetime.now()
total_during = total_end - total_start

print("total time consumed: %sus" % total_during.microseconds )
