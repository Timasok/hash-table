import pandas as pd
import matplotlib.pyplot as plt

caption = 'Hash func'
value = 'Dispersion'

df = pd.read_csv("./data_files/hash_funcs_cmp.csv")
funcs = df[caption]
disp = df[value]

# print('Hash funcs:', funcs)
# print('Disp:', disp)

# plt.xlim((0, x_max))
plt.bar(funcs, disp)
plt.xlabel(caption)
plt.ylabel(value)

plt.title(value)

result_name = "./analysis/" + value + "-results.png"

plt.savefig(result_name)
# plt.show()