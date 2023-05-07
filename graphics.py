# import pandas as pd
# import csv

import sys, getopt
import time
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('./data_files/data.csv', delimiter=',')

y_axis = []
x_axis = []

this_file_name = sys.argv[0]
hash_name = sys.argv[1].replace('_', ' ')

result_name = "./analysis/" + hash_name + "-results.png"

for i in range(1, len(data)):
    y_axis.append(data[i][1])
    x_axis.append(data[i][0]+1) 

plt.bar(x_axis, y_axis)
plt.xlabel('Index')
plt.ylabel('Collisions')

plt.title(hash_name)

# plt.show()
plt.savefig(result_name)

# time.sleep(5)
# plt.close()
