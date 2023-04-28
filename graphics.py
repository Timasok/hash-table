# import pandas as pd
# import csv

import sys, getopt
import time
import numpy as np
import matplotlib.pyplot as plt

#TODO make my own name of file
data = np.genfromtxt('./data_files/Illmatic-stat.csv', delimiter=',')

y_axis = []
x_axis = []

this_file_name = sys.argv[0]
hash_name = sys.argv[1]

result_name = "./analysis/" + hash_name + "-results.png"

for i in range(len(data)):
    y_axis.append(data[i][1])
    x_axis.append(data[i][0]) 

plt.bar(x_axis, y_axis, width = 1)
plt.xlabel('Index')
plt.ylabel('Collisions')

# plt.title(hash_name)

# plt.savefig(result_name)

plt.show()
# time.sleep(5)
# plt.close()
