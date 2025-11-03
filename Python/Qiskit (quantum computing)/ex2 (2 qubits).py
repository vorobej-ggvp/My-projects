from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt

# Creating the scheme with 2 qubits and 2 bits
qc = QuantumCircuit(2, 2)

# Adamar's gate in 1 qubit — creating superposition
qc.h(0)

# CNOT gate: if q0 == 1, then q1 is inverting => creating entanglement
qc.cx(0, 1)

# Measuring 2 qubits
qc.measure([0, 1], [0, 1])

# Drawing scheme
qc.draw('mpl')
plt.show()

# Starting the simulation
simulator = AerSimulator()
compiled_circuit = transpile(qc, simulator)
result = simulator.run(compiled_circuit, shots=1000).result()
counts = result.get_counts()

# Showing the measurments' result
plot_histogram(counts)
plt.show()

print(counts)