import numpy as np
import matplotlib.pyplot as plt
from json import dump, load

my_data_r = np.loadtxt("data_rand_walk.txt")
r = open('rand_walk.json', 'r')
config = load(r)
r.close()


    
k = np.linspace(0, config["steps"], config["steps"])

fig, axs = plt.subplots()
fig.suptitle('Random walks in N steps')
    
for i in range(config["particles"]):    
    axs.plot(k, my_data_r[:, i], color = 'g')


plt.grid(True)
plt.show()