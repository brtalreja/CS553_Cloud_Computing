import random
import string
import csv

test_data = []
keys = set()
for _ in range(1000):
    while True:
        key = "".join(random.sample(string.ascii_letters + string.digits, 10))
        value = []
        for _ in range(9):
            value.extend(random.sample(string.ascii_letters + string.digits, 10))
        value = "".join(value)
        if key not in keys:
            break
    keys.add(key) 
    test_data.append([key, value])

header = ['key', 'value']
with open('test_data.csv', 'w', encoding='utf-8', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(header)
    writer.writerows(test_data)

