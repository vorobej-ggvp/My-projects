import matplotlib.pyplot as plt
import numpy as np
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram, plot_state_qsphere

weights = [
    [0, 1001, 340, 341, 78],
    [1001, 0, 0, 2, 2],
    [340, 0, 0, 99, 5],
    [341, 2, 99, 0, 10],
    [78, 2, 5, 10, 0]
]

# 0 < norm_weights < 2pi
max_w = 1001
norm_weights = np.array(weights) / max_w

# 5 qubits for 5 knots
num_qubits = 5
qc = QuantumCircuit(num_qubits, num_qubits)

qc.h(range(num_qubits))
qc.barrier()

# Value layer (uses all weights from the matrix)
gamma = 1.0 # Learning parametre
for i in range(num_qubits):
    for j in range(i + 1, num_qubits):
        if norm_weights[i][j] > 0:
            qc.cp(2 * gamma * norm_weights[i][j], i, j)
qc.barrier()

# Mix layer 
beta = 0.5
qc.rx(2 * beta, range(num_qubits))
qc.barrier()

qc.save_statevector()

qc.measure(range(num_qubits), range(num_qubits))

sim = AerSimulator()
shots = 4096
result = sim.run(qc, shots=shots).result()
counts = result.get_counts()


print("Analysis: the higher column, the more optimal path is")
plot_histogram(counts, figsize=(12, 5))
plt.show()

qc.draw('mpl', scale=.6)
plt.show()

simul = AerSimulator(method='statevector')
result = simul.run(qc).result()
sv = result.get_statevector()

plot_state_qsphere(sv)
plt.show()