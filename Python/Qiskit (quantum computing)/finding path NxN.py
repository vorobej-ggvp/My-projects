import numpy as np
import matplotlib.pyplot as plt
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram, plot_state_city

rows, cols = 2, 3
n_qubits = rows * cols

weights = np.random.randint(1, 11, size=(rows, cols))
print("Weight matrix:\n", weights)

start_idx = 0
end_idx = n_qubits - 1

qc = QuantumCircuit(n_qubits)
others = [i for i in range(n_qubits) if i not in [start_idx, end_idx]]
qc.h(others)


qc.x([start_idx, end_idx])


# gamma = 3.535 # Coef of weight influence
# beta = .8 # To mix
penalty = .8 # Coef of fine for breaking the line
tax = .1 # Coef for path from (0, 0) point to (n-1, n-1) point
gamma_base = 1.2
p = 6

for layer in range(p):

    fraction = layer / (p - 1) if p > 1 else 1
    curr_gamma = gamma_base * (.2 + fraction ** 2)
    curr_beta = 1 - fraction

    # Coef of fading
    qc.rz(-np.pi / 2, start_idx)
    qc.rz(-np.pi / 2, end_idx)

    
    for r in range(rows):
        for c in range(cols):
            idx = r * cols + c

            # Weight for each knot
            node_weight = (tax + (curr_gamma * (weights[r, c] / 10) ** 2)) * np.pi
            qc.rz(node_weight, idx)

            # Connection with the right knot
            if c + 1 < cols:
                qc.cp(-penalty * np.pi, idx, r * cols + (c + 1))
            # Connection with the knot below
            if r + 1 < rows:
                qc.cp(-penalty * np.pi, idx, (r + 1) * cols + c)

    qc.rx(2 * curr_beta, range(n_qubits))
    qc.barrier()

qc.save_statevector()

sim = AerSimulator(method='statevector')
# optimization_level=3 makes computer compress the scheme
t_qc = transpile(qc, sim, optimization_level=3)

print(f"Depth before optimization: {qc.depth()}")
print(f"Depth after optimization: {t_qc.depth()}")

result = sim.run(t_qc).result()
statevector = result.get_statevector()

# Find max index in vector
best_idx = np.argmax(np.abs(statevector) ** 2)
# Convert to binary code from 28 bits
best_path_bin = format(best_idx, f'0{n_qubits}b')[::-1]

print(best_path_bin[0])
print(best_path_bin[5])

print(f"Most optimized path (in bits) is: {best_path_bin}")

path_map = np.array([int(b) for b in best_path_bin]).reshape(rows, cols)
print("Matrix of weights:\n", weights)
print("Path map: 1 - go, 0 - stay :\n", path_map)

plt.figure(figsize=(10, 6))
plt.imshow(path_map, 'YlGn')
for (j, i), label in np.ndenumerate(weights):
    color = 'white' if path_map[j, i] == 1 else 'black'
    plt.text(i, j, label, ha='center', va='center', color=color, fontweight='bold')
plt.title("Quantum path (from (0, 0) to (3, 6))")
plt.xlabel("Columns (0-6)")
plt.ylabel("Rows (0-3)")
plt.show()

# plot_state_city(statevector)
# plt.show()