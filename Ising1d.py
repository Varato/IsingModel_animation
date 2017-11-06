import numpy as np 
import matplotlib.pyplot as plt 
import sys

num_s = 1000
N = 1000000

def e(x):
    e = 0
    for i in range(len(x)):
        e += -x[i]*x[(i+1)%len(x)]
    return e

def p(T, e):
    return np.exp(-e/T)
x = np.random.choice((-1,1), size = num_s)
ee = np.zeros(N)
T = .5

for i in range(N):
    print("\ri={}".format(i), end="")
    sys.stdout.flush()
    r_site = np.random.randint(0, num_s)
    de = 2*x[r_site] * ( x[(r_site-1)%num_s] + x[(r_site+1)%num_s] )
    ratio = np.exp(-de/T)
    if ratio >= 1 or np.random.random() < ratio:
        x[r_site] *= -1
    ee[i] = e(x)
print()




plt.hist(ee, bins = 100, normed = True)
plt.savefig("/home/chen/Dropbox/1dising.png")
# plt.show()



