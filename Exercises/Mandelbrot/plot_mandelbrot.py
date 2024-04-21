#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 25 14:51:47 2019

@author: aknebe
"""

import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("./mandelbrot.dat")

x = data[:,0]
y = data[:,1]
n = data[:,2]

xmin = np.min(x)
xmax = np.max(x)
ymin = np.min(y)
ymax = np.max(y)
print('x = [',xmin,',',xmax,']')
print('y = [',ymin,',',ymax,']')

nmin = np.min(n)
nmax = np.max(n)
print('n = [',nmin,',',nmax,']')
n = n/nmax

plt.figure()
plt.scatter(x,y, c=n, s=4, cmap='jet', edgecolors='none')
plt.colorbar()
plt.savefig('mandelbrot_plot.pdf')
plt.xlim([xmin,xmax])
plt.ylim([ymin,ymax])
plt.show()
