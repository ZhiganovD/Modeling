import numpy as np
import matplotlib.pyplot as plt
from json import dump, load

my_data_r = np.loadtxt("data1.0.txt")
r = open('rand_input.json', 'r')
config = load(r)
r.close()

x_r = []
for i in range(0, config["n"]):
    x_r.append(my_data_r[i])
    
n, bins, patches = plt.hist(x_r, config["bins"], density=True, facecolor='g', alpha=0.75)

plt.grid(True)
plt.show()
