import numpy as np
import random
import matplotlib.pyplot as plt

def modelcompar(t, x1, y1, x2, y2, x3, y3, y2_2, y3_2):
    fig, axs = plt.subplots(2, 3)
    fig.suptitle('A tale of 6 subplots')

    axs[0, 0].plot(t, x2, color = 'g')
    axs[1, 0].plot(t, x3, color = 'b')
    axs[0, 0].plot(x1, y1, color='r', label='sin')
    axs[1, 0].plot(x1, y1, color='r', label='sin')
    axs[1, 0].set_xlabel('Oscillation')

    axs[0, 1].plot(x2, y2, color = 'g')
    axs[1, 1].plot(x3, y3, color = 'b')
    #ax2.set_xlabel('time (s)')
    axs[1, 1].set_xlabel('Diagramm')

    axs[0, 2].plot(t, y2_2, color = 'g')
    axs[1, 2].plot(t, y3_2, color = 'b')
    axs[1, 2].set_xlabel('Energy')
    
    plt.show()

def acc(t, x2, k):
    #k = random.randint(50000, 99999)
    T = t[k]
    return abs(x2[k] - np.sin(omega * T + 0))

def acccompar(t, a_e, a_h, diff):
    fig, axs = plt.subplots(3)
    fig.suptitle('Accuracies')

    axs[0].plot(t, a_e, color = 'g')

    axs[1].plot(t, a_h, color = 'g')

    axs[2].plot(t, diff, color = 'g')
    
    plt.show()

my_data_e = np.loadtxt("data0_1.txt")
my_data_h = np.loadtxt("data1_1.txt")
#print(my_data)

n = int(my_data_e[0][0])
omega = my_data_e[0][1]
x1 = np.linspace(0.0, 1000.0, 100000)
y1 = np.sin(omega * x1 + 0)
#y1 = np.sin(x1)

x2 = []
y2 = []
y2_2 = []
for i in range(1, n + 1):
    x2.append(my_data_e[i][0])
    y2.append(my_data_e[i][1])
    y2_2.append(pow(my_data_e[i][1], 2))
    
x3 = []
y3 = []
y3_2 = []
for i in range(1, n + 1):
    x3.append(my_data_h[i][0])
    y3.append(my_data_h[i][1])
    y3_2.append(pow(my_data_h[i][1], 2))
    
t = np.linspace(0, len(my_data_e)*0.01, len(my_data_e)-1)

a_e = []
a_h = []
diff = []
for i in range(0, 100000):
    a_e.append(acc(t, x2, i))
    a_h.append(acc(t, x3, i))
    diff.append(abs(a_e[i] - a_h[i]))

modelcompar(t, x1, y1, x2, y2, x3, y3, y2_2, y3_2)

#acccompar(t, a_e, a_h, diff)

