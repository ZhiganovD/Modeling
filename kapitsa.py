import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def damp(t, x, y, y2):
    fig, axs = plt.subplots(3)
    fig.suptitle('Damped osc')
    
    axs[0].plot(t, x, color = 'g')

    axs[1].plot(x, y, color = 'g')

    axs[2].plot(t, y2, color = 'g')

    
    plt.show()
    


my_data_k = np.loadtxt("data0_2.txt")

#print(my_data)

n = int(my_data_k[0][0])
omega = my_data_k[0][1]
#y1 = np.sin(x1)

x_k = []
y_k = []
y_k_2 = []
for i in range(1, n + 1):
    x_k.append(my_data_k[i][0])
    y_k.append(my_data_k[i][1])
    y_k_2.append(pow(my_data_k[i][1], 2))
       
t = np.linspace(0, len(my_data_k)*0.01, len(my_data_k)-1)

damp(t, x_k, y_k, y_k_2)



