import numpy as np
import matplotlib.pyplot as plt
from sys import exit

D = 1.
v = 10.
Dr = 0.5
tr = 2*Dr


def f(t):
    A = (4*D + 2*v*v*tr) * t
    B = np.exp(-t/tr) - 1
    B *= 2*v*v*tr*tr
    return A + B



msdX = np.loadtxt("msdX.dat")
msdY = np.loadtxt("msdY.dat")
msdZ = np.loadtxt("msdZ.dat")



tmin = msdX[1,0]
tmax = msdX[-1,0]
ymin = msdX[1,1]
ymax = msdX[-1,1]

t = np.logspace( np.log(tmin), np.log(tmax), 100)

#plt.scatter(msdX[:,0], (msdX[:,1]+msdY[:,1]+msdZ[:,1]))
plt.plot(t,f(t),color="black",ls=":")
plt.xscale("log")
plt.yscale("log")
plt.xlim([tmin, tmax])
plt.ylim([ymin, ymax])
#plt.show()


x = []
y = []
i = 0
I = 0
di = 1
a = 1.25
while i < len(msdX):
    print(i)
    x.append(msdX[i,0])
    y.append(msdX[i,1] + msdY[i,1] + msdZ[i,1])
    I += di
    i += int(di)
    di *= a

plt.scatter(x,y)
plt.show()
    
