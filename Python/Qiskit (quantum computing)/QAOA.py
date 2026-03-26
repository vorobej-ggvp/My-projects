import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector
from scipy.optimize import minimize

# Grid 2x2: 0--1--2
#           |  |  |
#           3--4--5
# weights = [0, 10, 10, 1, 1, 0]
weights = [0, 1, 10, 10, 1, 0]
edges = [(0, 1), (1, 2), (3, 4), (4, 5), (0, 3), (1, 4), (2, 5)]
n_qubits = 6
np.random.seed(42)

W_SCALE = 2.0
P_CONN = 10.0
P_LEN = 50.0 

def create_QOAO(params, p = 2):
    gamma = params[:p]
    beta = params[p:]
    qc = QuantumCircuit(n_qubits)
    qc.h(range(n_qubits))

    for j in range(p):
        for i in range(n_qubits):
            qc.rz(-gamma[j] * ((weights[i] * W_SCALE)), i)

        for u, v in edges:
            qc.rzz(gamma[j] * P_CONN, u, v)

        qc.rz(-gamma[j] * 100, 0)
        qc.rz(-gamma[j] * 100, 5)

        qc.rx(2 * beta[j], range(n_qubits))
    return qc

initial_guess = [.1, .1, .1, .1]

def compute_energy(params):
    qc = create_QOAO(params, p=2)
    state = Statevector.from_instruction(qc)
    probs = state.probabilities_dict()

    total_energy = 0
    for bitstring, prob in probs.items():
        x = [int(b) for b in bitstring[::-1]]
        
        score = 0
        if x[0] == 1 and x[5] == 1:
            score += 1000
        else:
            score -= 5000
            
        active_links = sum(1 for i, j in edges if x[i] and x[j])
        score += active_links * 200
        
        score -= sum(x[i] * weights[i] for i in range(n_qubits)) * 5
        
        score -= abs(sum(x) - 4) * 1000
        
        total_energy += prob * (-score)
    return total_energy

# P_CONN = 5
# P_ANC = 10.0

# def create_QOAO(params, p = 2):
#     gamma = params[:p]
#     beta = params[p:]

#     qc = QuantumCircuit(n_qubits)
#     qc.h(range(n_qubits))

#     deg = [0] * n_qubits
#     for u, v in edges:
#         deg[u] += 1
#         deg[v] += 1

#     for j in range(p):
#         for i in range(n_qubits):
#             # 11 good, 00 bad
#             h_i = -weights[i] + (P_CONN * deg[i] / 2.0)

#             # start and finish
#             if i == 0 or i == 5:
#                 h_i -= P_ANC

#             # filtering weights
#             qc.rz(-gamma[j] * h_i, i)

#         for u, v in edges:
#             qc.rzz(-gamma[j] * (P_CONN / 2.0), u, v)

#         # tunnel (mixer)
#         qc.rx(2 * beta[j], range(n_qubits))

#     return qc

# initial_guess = [.1, .1, .1, .1]

# def compute_energy(params):
#     qc = create_QOAO(params, p=2)
#     state = Statevector.from_instruction(qc)
#     probs = state.probabilities_dict()

#     total_energy = 0
#     for bitstring, prob in probs.items():
#         x = [int(b) for b in bitstring[::-1]]

#         cost = sum(x[i] * weights[i] for i in range(n_qubits))

#         active_links = sum(1 for i, k in edges if x[i] and x[k])
#         cost -= P_CONN * active_links

#         cost += 10.0 * (sum(x) - 4) ** 2

#         if x[0] == 0: cost += 20
#         if x[5] == 0: cost += 20

#         total_energy = prob * cost
#     return total_energy

def plot_quantum_path(bitstring, rows=2, cols=2):
    x = [int(b) for b in bitstring[::-1]]

    G = nx.grid_2d_graph(rows, cols)
    pos = {(r, c): (c, -r) for r in range(rows) for c in range(cols)}

    node_map = {i: (i // cols, i % cols) for i in range(len(x))}

    node_colors = []
    for i in range(len(x)):
        if x[i] == 1:
            node_colors.append('#00ff00')
        else:
            node_colors.append('#eeeeee')
    
    plt.figure(figsize=(5, 5))
    nx.draw(G, pos, node_color=node_colors, with_labels=True, node_size=1200, font_weight='bold', edge_color='#bbbbbb')

    plt.title(f"Found path is: {bitstring}")
    plt.show()

    
res = minimize(compute_energy, initial_guess, method="COBYLA", options={'maxiter': 200})

final_qc = create_QOAO(res.x)
final_state = Statevector.from_instruction(final_qc)
counts = final_state.sample_counts(4000)

print(f"Optimized params are: gamma={res.x[0]:.2f}, beta={res.x[1]:.2f}")
print("Top-3 most optimized results (bytes is probability): ")
sorted_counts = sorted(counts.items(), key=lambda x: x[1], reverse=True)
for i in range(3):
    print((f"Path {sorted_counts[i][0]}: {sorted_counts[i][1] / 1024:.2%}"))

plot_quantum_path(sorted_counts[0][0], 2, 3)
