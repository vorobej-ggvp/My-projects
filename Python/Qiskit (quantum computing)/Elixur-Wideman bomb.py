# We have bomb with supersensetive detonator - if photon gets on it bomb explodes
# We can check if bomb exists without looking at it (so photon aka light don't gets on it) by using quantum interferation
# How it works:
# 1. Create interferometer (gates H)                                                   
# 2. Photon in superposition choosing path A or path B
# 3. No bomb - paths intersected, interferention happens, photon ALWAYS goes to path A
# 4. Bomb - it "measures" photon, superposition collpasing, no interferention, photon goes EITHER path A or path B
# 5. In ~50% cases photon will go to path B so if we found it in path B => boomb exists

import matplotlib.pyplot as plt
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator

def bomb_tester(bomb_present):
    qc = QuantumCircuit(1, 1)

    # Photon goes into interferometer (create superposition)
    qc.h(0)

    # Bomb "measures" path
    if bomb_present:
        # If bomb exists it makes photon choose one path (collapse)
        qc.measure(0, 0)
        # If bomb didn't explode (rolled 0) continue the experiment
        # For simulation gate H again to see the reaction
        qc.h(0)
    else:
        # If bomb doesn't exist photon goes through and again gate H
        qc.h(0)
    
    qc.measure(0, 0)
    return qc

sim = AerSimulator()

qc_no_bomb = bomb_tester(False)
res_no_bomb = sim.run(qc_no_bomb, shots=1000).result().get_counts()

qc_bomb = bomb_tester(True)
res_bomb = sim.run(qc_bomb, shots=1000).result().get_counts()

print(f"No bomb - always zero: {res_no_bomb}")
print(f"Bomb - chance to get 1: {res_bomb}")

qc_bomb.draw('mpl')
plt.show()