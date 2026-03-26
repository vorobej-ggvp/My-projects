# Alice want to share the password to Bob.
# There's 3 qubits: qc[0] - Alice's qubit with secret state, qc[1] - Alice's qubit, qc[2] - Bob's qubit.
# qr[1] and qr[2] are entangled.

from qiskit import QuantumCircuit, transpile
from qiskit_aer import AerSimulator
import matplotlib.pyplot as plt
from qiskit.visualization import plot_histogram

# 3 qubits, 1 secret qubit, 2 bits with info
qc = QuantumCircuit(3, 2)

# Make qc[0] (secret) state as superposition
qc.h(0)
qc.rz(0.5, 0) # Add phase so secret will be more complex (makes it rotate)
qc.barrier(label="Alice: secret")

# Make qc[1] state as superposition
qc.h(1)
qc.cx(1, 2) # Entangle Alice's and Bob's qubits
qc.barrier(label="Entanglement for Bob")

# Alice measures her secret qc[0] qubit and her qc[1] qubit
qc.cx(0, 1) # Secret and pure qubits should interact
qc.h(0)
qc.barrier(label="Alice: measuremants")

# Alice record her states to bits so info would be saved and can be shared
qc.measure(0, 0)
qc.measure(1, 1)
qc.barrier(label="Alice: Share keys")

# Bob received bits with info and canges his qubits to decrypt secret qubit
with qc.if_test((0, 1)): # if bit = 0 Bob uses X for his qubit
    qc.x(2)
with qc.if_test((1, 1)): # if bit = 1 Bob uses Z for his qubit
    qc.z(2)
qc.barrier(label="Bob: decryption")

print("Scheme of quantum teleportation")
qc.draw(output='mpl', filename='teleportation.png', scale=.7)

simulator = AerSimulator()
compiled_circuit = transpile(qc, simulator)
job = simulator.run(compiled_circuit, shots=1000)
result = job.result()
counts = result.get_counts(qc)
plt.show()

print(counts)