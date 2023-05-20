import numpy as np
import matplotlib.pyplot as plt
from json import dump, load


def draw(k, mode, x_1d= None, iter = None, x_2d = None, rows = None):
    if mode == "1d":
        for i in range(iter):
            if (i % 1000 == 0):
                plt.plot(k, x_1d[i])
                
    if mode == "2d":
        for i in range (rows):
            plt.plot(k, x_2d[i], label = f'Line {i+1}')

my_data_r_1d = np.loadtxt("task_1d.txt")
my_data_r_2d = np.loadtxt("task_2d.txt")
r = open('task.json', 'r')
config = load(r)
r.close()

mode = '1d'

if mode == '1d':
    k_1d = np.linspace(0, config["rows"], config["rows"])
    x_1d = []
    for i in range(0, config["iter"]):
        r = []
        for j in range(0, config["rows"]):
            r.append(my_data_r_1d[i][j])
        x_1d.append(r)

if mode == '2d':
    k_2d = np.linspace(0, config["columns"], config["columns"])  
    x_2d = []
    for i in range(0, config["rows"]):
        r = []
        for j in range(0, config["columns"]):
            r.append(my_data_r_2d[i - config["rows"]][j])
        x_2d.append(r)
    
fig, ax = plt.subplots() 
#c = ax.pcolor(x_2d)
#ax.bar(names, x_r)
draw(k_1d, mode, x_1d = x_1d, iter = config["iter"])



plt.grid(True)
plt.legend(fontsize=5)
plt.show()
