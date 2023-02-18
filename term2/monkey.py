import numpy as np
import matplotlib.pyplot as plt
from json import dump, load


my_data_r = np.loadtxt("data3.0.txt")
r = open('rand_input.json', 'r')
config = load(r)
r.close()

x_r = []
names = []
for i in range(0, 27):
    x_r.append(my_data_r[i, 1])
    names.append(str(int(my_data_r[i, 0])))

    
fig, ax = plt.subplots() 

ax.bar(names, x_r)



plt.grid(True)
plt.show()
