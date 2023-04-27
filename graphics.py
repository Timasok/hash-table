# import pandas as pd
# import csv

import sys, getopt
import time
import numpy as np
import matplotlib.pyplot as plt

#TODO make my own name of file
data = np.genfromtxt('./files/Illmatic-stat.csv', delimiter=',')

y_axis = []
x_axis = []

hash_name = sys.argv[1]

for i in range(len(data)):
    y_axis.append(data[i][1])
    x_axis.append(data[i][0]) 

plt.bar(x_axis, y_axis, width = 0.7)
plt.xlabel('Index')
plt.ylabel('Collisions')
plt.title(hash_name)

# plt.show()
# time.sleep(5)
# plt.close()

plt.savefig("./files/bebra.png")

# print(data[i][1])

    # y_axis.append(plt.figure(figsize=(3, 3)))
    # x_axis.append(y_axis[i].add_subplot(1,1,1))


# with open("./files/Illmatic-stat.csv", 'r') as file:
#     csvreader = csv.reader(file)     # allows to address to rows via names

#     next(csvreader)

#     for row in csvreader:
#         y_axis.append(row[1]) 
#         x_axis.append(row[0]) 

#     collisions = np.array(y_axis)
#     index      = np.array(x_axis)

#     print(collisions[1] + index[1])
# print(index)

# hash_funcs = ["Length Hash","FirstAscii", "Hashsum", "Ror Hash", "Rol Hash", "Murmur hash"]

# collisions = np.array ([589413, 8954, 28424, 189, 178, 93, 15])
# index = np.array([1, 2, 3, 4, 5, 6])


# plt.bar(x_axis, y_axis, align ='center')
# plt.xticks(x_axis, index)

#     plt.bar(x_axis, y_axis)
#     plt.xlabel('index')
#     plt.ylabel('collisions')

#     plt.show()

# f.readline()

# plt.show()
