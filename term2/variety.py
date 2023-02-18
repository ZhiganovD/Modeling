import numpy as np
import matplotlib.pyplot as plt
from json import dump, load

my_data_r = np.loadtxt("data2.0.txt")
r = open('rand_input.json', 'r')
config = load(r)
r.close()

x_r = []
y_r = []
for i in range(0, config["n"] - config["k"]):
    x_r.append(my_data_r[i, 0])
    y_r.append(my_data_r[i, 1])
    
fig, axs = plt.subplots()
fig.suptitle('All K numbers in N attempts')
    
axs.plot(x_r, y_r, color = 'g', label = 'K = ' + str(config["k"]))
axs.set_xlabel('Number of attempts')
axs.set_ylabel('Probability')
axs.legend()
plt.grid(True)   
plt.show()


