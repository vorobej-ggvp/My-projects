from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
from qiskit.visualization import plot_histogram
import matplotlib.pyplot as plt
import numpy as np

def create_teleportation_circuit(eavesdrop):
    qc = QuantumCircuit(3, 3)

    qc.h(0)
    qc.s(0) # Gate S from X to Y
    qc.barrier()

    qc.h(1)
    qc.cx(1, 2)
    qc.barrier()

    if eavesdrop:
        qc.measure(2, 2)
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
    
    qc.sdg(2) # Return to X
    qc.h(2) # Return to Z
    qc.measure(2, 2)
    
    return qc

simulator = AerSimulator()
total_counts = {}

for _ in range(100):
    is_eve_here = np.random.choice([True, False])
    current_qc = create_teleportation_circuit(is_eve_here)
    result = simulator.run(current_qc).result()
    c = result.get_counts()

    for k, v in c.items():
        total_counts[k] = total_counts.get(k, 0) + v

plot_histogram(total_counts)
plt.show()