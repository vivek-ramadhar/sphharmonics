import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("./data/sph.txt")

x = data[:,0]
y = data[:,1]
z = data[:,2]


fig = plt.figure(figsize=(10,8))
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x, y, z, c=z, cmap='viridis', s=3)

ax.set_xlabel('X')
ax.set_xlabel('Y')
ax.set_xlabel('Z')

ax.set_box_aspect([1,1,1])

plt.tight_layout()
plt.show()

