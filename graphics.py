import csv
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

values = []
x_axis = []

# with open("./files/Illmatic-stat.csv", 'r') as file:
#     csvreader = csv.reader(file)     # allows to address to rows via names

#     next(csvreader)

#     for row in csvreader:
#         values.append(row[1]) 
#         x_axis.append(row[0]) 

#     print(values)

#     range = (0, 99)
#     # plt.hist(values, 99, range, color = 'blue', histtype = 'bar')

#     plt.hist(values, 200)
#     plt.xlabel('index')
#     plt.ylabel('chain length')

#     plt.show()


data = np.genfromtxt('./files/Illmatic-stat.csv', delimiter=',')

fig_arr = []
plt_arr = []

for i in range(len(data)):
    fig_arr.append(plt.figure(figsize = (3, 3)))
    plt_arr.append(fig_arr[i].add_subplot(1, 1, 1))
    plt_arr[i].bar(list(range(len(data[i]))), data[i])

plt.show()