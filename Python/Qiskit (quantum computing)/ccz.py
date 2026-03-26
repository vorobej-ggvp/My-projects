import matplotlib.pyplot as plt
from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator

qc = QuantumCircuit(3)

qc.ccz(0, 1, 2)

print("Before transpile:")
qc.draw('mpl')
plt.show()

sim = AerSimulator()
transpiled_qc = transpile(qc, basis_gates=['cx', 'id', 'rz', 'sx', 'x'], optimization_level=1)

print("After transpile:")
transpiled_qc.draw('mpl')
plt.show()