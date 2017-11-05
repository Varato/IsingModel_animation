import matplotlib.pyplot as plt
import numpy as np

ls = plt.imread("ising100T15.png")
cs = plt.imread("ising100Tc.png")
hs = plt.imread("ising100T5.png")
imgs = [ls, cs, hs]
titles = ["low T", "critical", "high T"]
fig0, axes = plt.subplots(ncols = len(imgs), figsize = [14,6])

for i, ax in enumerate(axes):
    ax.imshow(imgs[i])
    ax.set_title(titles[i])
    ax.set_xticks([])
    ax.set_yticks([])

# l = np.loadtxt("energy_data_15_100_100")
# c = np.loadtxt("energy_data_c_100_100")
# h = np.loadtxt("energy_data_50_100_100")

# bins = np.arange(-20000, 0, 10)

# fig, ax = plt.subplots(ncols=1)
# ax.hist(l, bins = bins, color = "blue")
# ax.hist(c, bins = bins, color = "cyan")
# ax.hist(h, bins = bins, color = "red")


# ax.set_title("100*100 spins @kT = 1.5, 2.26 and 5.0")
# ax.set_xlabel("E/J")
# ax.set_ylabel("counts")



plt.tight_layout()
plt.savefig("spins.png", dpi = 200)
plt.show()