import matplotlib.pyplot as plt
import numpy as np

c = np.loadtxt("res.txt", delimiter=",")

# c = np.array([0.59375, 0.171875, 0.90625, 8.45312, 
#     33.2344, 99.4375, 247.328, 504.312, 979.594, 
#     2004.88, 1761.81, 1187.05, 1015.88, 886.629, 
#     827.578, 807.189, 740.732, 713.217, 699.514, 669.992, ])

T = np.arange(0.5, 3, 0.1)

print(c.shape, T.shape)
plt.plot(T, c, "o")
plt.show()