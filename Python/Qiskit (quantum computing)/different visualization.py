import matplotlib.pyplot as plt
import numpy as np
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_bloch_multivector, plot_state_city, plot_state_qsphere

qc = QuantumCircuit(2)
qc.h(0)
qc.ry(np.pi / 12, 1)
qc.cx(0, 1)
qc.save_statevector()

# Get state vector
sim = AerSimulator(method='statevector')
result = sim.run(qc).result()
statevector = result.get_statevector()

# Bloch's sphere - cubits as arrows
plot_bloch_multivector(statevector)
plt.show()

# QSphere - entanglement and phases as circles and colours
plot_state_qsphere(statevector)
plt.show()

# State city - 3D columns, showing real and imaginary sides of matrix
plot_state_city(statevector)
plt.show()