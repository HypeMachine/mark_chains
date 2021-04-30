import numpy as np
import matplotlib.pyplot as plt

# ? Get values of states
NUM_STEPS = np.genfromtxt(
    "//opt//c++//IKSS//scripts//vectors.txt", dtype=int, max_rows=1, deletechars=" ")
vstates = np.genfromtxt(
    "//opt//c++//IKSS//scripts//vectors.txt", delimiter=", ", dtype=float, skip_header=1, max_rows=1, deletechars=" ")
# ? Get values of probabilitys
vro = np.genfromtxt(
    "//opt//c++//IKSS//scripts//vectors.txt", delimiter=", ", dtype=float, skip_header=2, deletechars=" ")
# print(NUM_STEPS)
print(vstates)
# print(vro)
plt.figure()
# ? plot "vstates"
plt.axis([0, NUM_STEPS, 0, 1.0])
plt.plot(vstates)
plt.xlabel("Step")
plt.ylabel("State")
plt.savefig("//opt//c++//IKSS//graphics//state_switching.jpeg")
plt.figure()
# ? plot "vro"
plt.axis([0, NUM_STEPS, 0, 1])
num = 1
for vector in vro:
    plt.plot(vector, label=("State" + str(num)))
    num += 1
plt.xlabel("Probability of state")
plt.ylabel("Time")
plt.legend()
plt.savefig("//opt//c++//IKSS//graphics//state_probs.jpeg")
