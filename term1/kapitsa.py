import numpy as np
import matplotlib.pyplot as plt
from json import dump, load
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

#damp(t, x_k, y_k, y_k_2)

r = open('kapitsa_input.json', 'r')
config = load(r)
r.close()

FPS = 10

L = config['l']
H = config['l'] + config['ampl']

fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(autoscale_on=False, xlim=(-1.02*L, 1.02*L), ylim=(-1.02*H, 1.02*H))
ax.set_aspect('equal')
ax.grid(True, alpha=.3)

line, = ax.plot([], [], 'o-', lw=2, zorder=2)
trace, = ax.plot([], [], '.-', lw=1, ms=2, zorder=1)
time_template = 'time = %.1fs'
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

t = np.arange(0, config['time'], config['dt'])
x = config['l'] * np.sin(x_k)
y =-config['l'] * np.cos(x_k) + config['ampl'] * np.cos(config['nu'] * config['dt'] * np.arange(len(my_data_k) - 1))
ax.set_xlim(min(x), max(x))
ax.set_ylim(min(min(y)-L, -config['ampl']), max(max(y)+L, config['ampl']))

def animate(i):
    thisx = [0, x[i]]
    thisy = [config['ampl'] * np.cos(config['nu'] * config['dt'] * i), y[i]]

    line.set_data(thisx, thisy)
    if i > len(x):
        trace.set_data(x[0], y[0])
    else:
        trace.set_data(x[:i], y[:i])

    time_text.set_text(time_template % (i * config['dt']))
    return line, trace, time_text

ani = FuncAnimation(fig, animate,
    frames=np.arange(0, int(config['time'] / config['dt'])),
    blit = True, interval = FPS)# int(.1 / config['modeling']['dt']))

plt.show()



