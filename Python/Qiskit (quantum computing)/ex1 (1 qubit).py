from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt

# Creating quantum scheme: 1 qubit and 1 bit
qc = QuantumCircuit(1, 1)

# Aplying Adamar's gate — creating superposition
qc.h(0)

# Measuring qubit
qc.measure(0, 0)

# Visualizating the scheme
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
