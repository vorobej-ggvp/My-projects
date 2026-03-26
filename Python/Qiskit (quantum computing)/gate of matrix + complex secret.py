import matplotlib.pyplot as plt
import numpy as np
from qiskit import QuantumCircuit, transpile
from qiskit.quantum_info import Operator
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram

# Create gate of matrix with some rotation
theta = np.pi / 5 # 36 degree
matrix = [
    [np.cos(theta), -np.sin(theta)],
    [np.sin(theta), np.cos(theta)]
]
custom_gate = Operator(matrix)

# Complex gate and tp
qc = QuantumCircuit(3, 3)

number = np.random.randint(1, 37)
qc.ry(np.pi / number, 0) # Rotate RY to random degree (numbers f=in denominator from 1 to 36) + custom gate
qc.unitary(custom_gate, [0], label='MyGate')
qc.barrier()

qc.cx(0, 1)
qc.h(0)
qc.measure(0, 0)
qc.measure(1, 1)
qc.barrier()

with qc.if_test((qc.clbits[1], 1)):
    qc.x(2)
with qc.if_test((qc.clbits[0], 1)):
    qc.z(2)

# Make unverse operations
qc.unitary(custom_gate.adjoint(), [2], label='MyGate_inv')
qc.ry(-np.pi / number, 2)
qc.measure(2, 2)

qc.draw('mpl')
plt.show()

t_qc = transpile(qc, basis_gates=['u', 'cx'], optimization_level=1)
print("Transpiled custom gate:")
t_qc.draw('mpl')
plt.show()

sim = AerSimulator()
counts = sim.run(qc, shots=1024).result().get_counts()
plot_histogram(counts)
plt.show()