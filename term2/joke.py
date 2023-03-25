import numpy as np
import matplotlib.pyplot as plt
from json import dump, load

my_data_r = np.loadtxt("joke.txt")
r = open('joke.json', 'r')
config = load(r)
r.close()


    
#k = np.linspace(0, config["steps"], config["steps"])
k = my_data_r[-1]
count = 0
#while (k[count] < 3.5):
#    count += 1

    

fig, axs = plt.subplots()

x = my_data_r[0][0]
alpha = config["alpha"]
fig.suptitle('Subsequence in %(N)s steps with x0 = %(x)s,  alpha = %(alpha)s' %  {"x" : x, "alpha" : alpha, "N" : config["steps"]})

l1 = config["steps"] // 2
l2 = config["steps"]
for i in range(l1, l2):    
    axs.scatter(k[count : ], my_data_r[i][count : ], color = 'g', s = 1)


    
#axs.plot(k, my_data_r[:, config["particles"]], color = 'r')
#axs.plot(k, my_data_r[-2], color = 'r')
axs.set_xlabel('Alpha')
axs.set_ylabel('Value')
#plt.xscale('log')


plt.grid(True)
plt.show()