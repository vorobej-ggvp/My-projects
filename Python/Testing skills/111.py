from numpy import random
import matplotlib.pyplot as plt
import seaborn as sns

# sns.displot(random.pareto(a=100000, size=1000))

x = random.zipf(a=1.5, size=1000)

# plt.show()

print(x)