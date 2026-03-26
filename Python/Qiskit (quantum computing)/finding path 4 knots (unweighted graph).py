import matplotlib.pyplot as plt
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram

# 4 knots == 2 qubits (00, 01, 10, 11)
qc = QuantumCircuit(2, 2)

# Create superposition = looking at all ways
qc.h([0, 1])
qc.barrier()

# Let's acheive qc[3] - 11

# For 11 oracul is cz
qc.cz(0, 1)
qc.barrier(label="Oracul")

# Diffusor (enhance correct result)
qc.h([0, 1])
qc.z([0, 1])
qc.cz(0, 1)
qc.h([0, 1])
qc.barrier(label="Diffusor")

qc.measure([0, 1], [0, 1])

sim = AerSimulator()
counts = sim.run(qc).result().get_counts()

print("Probabiity on '11' knot's side:")
plot_histogram(counts)
plt.show()