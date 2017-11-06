import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("edata", delimiter = ",")

e_ave = data[:,0]
c = data[:,1]
T = np.arange(1.5, 3.5, 0.2)

# plt.plot(T, e_ave/32/32)

plt.plot(T, c)
plt.show()