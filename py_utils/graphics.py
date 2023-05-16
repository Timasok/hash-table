# import pandas as pd
# import time

import csv
import sys
import numpy as np
import matplotlib.pyplot as plt
from colorama import Fore, Back, Style

data = np.genfromtxt('./data_files/data.csv', delimiter=',')

y_axis = []
x_axis = []

this_file_name = sys.argv[0]
hash_name = sys.argv[1].replace('_', ' ')
x_max = int(sys.argv[2])

result_name = "./analysis/" + sys.argv[1] + "-results.png"

for i in range(1, len(data)):
    y_axis.append(data[i][1])
    x_axis.append(data[i][0]+1) 

derivation = np.std(y_axis)**2
print(Fore.GREEN + hash_name + Fore.WHITE + ' derivation = ' + "%2.2lf" % derivation)

plt.xlim((0, x_max))
plt.bar(x_axis, y_axis)
plt.xlabel('Index')
plt.ylabel('Collisions')

plt.title(hash_name)

# plt.show()
plt.savefig(result_name)

with open('./data_files/hash_funcs_cmp.csv', 'a', newline='') as file:
    writer = csv.writer(file)
    field = []
    field.append(hash_name)
    field.append(derivation)
    
    writer.writerow(field)

# time.sleep(5)
# plt.close()
