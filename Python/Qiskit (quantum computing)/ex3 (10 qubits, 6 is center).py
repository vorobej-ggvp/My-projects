from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt

# Creating the scheme with 2 qubits and 2 bits
n = 10
center = 6
qc = QuantumCircuit(n, n)

# Adamar's gate in 1 qubit — creating superposition
qc.h(center)

# CNOT gate: if q0 == 1, then q1 is inverting => creating entanglement
for i in range(n):
    if i != center:
        qc.cx(center, i)

# Measuring 2 qubits
qc.measure(range(n), range(n))

# Drawing scheme
qc.draw('mpl')
plt.show()

# Starting the simulation
simulator = AerSimulator()
compiled_circuit = transpile(qc, simulator)
result = simulator.run(compiled_circuit, shots=1000).result()
counts = result.get_counts()

# Showing the measurments' result
print(counts)
plot_histogram(counts)
plt.show()
