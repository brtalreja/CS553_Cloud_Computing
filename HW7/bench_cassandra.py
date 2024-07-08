from cassandra.cluster import Cluster
import csv
import datetime

test_data = []
with open('test_data.csv', encoding='utf-8') as f:
     reader = csv.DictReader(f)
     for row in reader:
         test_data.append((row['key'], row['value']))

test_size = len(test_data)
print("test_data size:%d" % test_size)

cluster = Cluster(["10.102.22.107"])
session = cluster.connect()
keyspacename = "kv_space"
session.execute("create keyspace if not exists %s with replication = {'class': 'SimpleStrategy', 'replication_factor': 2};" % keyspacename)
session.set_keyspace(keyspacename)

s = session

s.execute("DROP TABLE IF EXISTS kvpair")
s.execute("CREATE TABLE kvpair (k text PRIMARY KEY, v text)")

total_start = datetime.datetime.now()

# insert
start = datetime.datetime.now()

for i in range(1000):
    s.execute("INSERT INTO kvpair (k, v) VALUES (%s, %s)", [test_data[i][0], test_data[i][1]])

end = datetime.datetime.now()

inserttime = end - start
print("insert %d items time consumed: %sus" % (test_size, inserttime.microseconds) )

# lookup

start = datetime.datetime.now()

for i in range(1000):
    s.execute("SELECT k, v from kvpair where k = %s", [test_data[i][0]])

end = datetime.datetime.now()

lookuptime = end - start
print("lookup %d items time consumed: %sus" % (test_size, lookuptime.microseconds) )

# delete

start = datetime.datetime.now()

for i in range(1000):
    s.execute("DELETE from kvpair where k = %s", [test_data[i][0]])

end = datetime.datetime.now()

deletetime = end - start
print("delete %d items time consumed: %sus" % (test_size, deletetime.microseconds) )

# total
# total_end = datetime.datetime.now()
total_during = inserttime.microseconds + lookuptime.microseconds + deletetime.microseconds; #total_end - total_start
average = total_during / 3;

print("total time consumed: %sus" % total_during)
print("average time consumed: %sus" % average)
