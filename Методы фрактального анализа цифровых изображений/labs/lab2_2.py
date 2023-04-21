import numpy as np
import matplotlib.pyplot as plt

POWER = 5

def func(x: float) -> float:
    if x > 1:
        return 0
    r = 1.5
    return 2*r*x if x < 0.5 else 2*r*(1-x)


def top(pow: int, points):
    res = points
    for i in range(pow):
        res = [func(x) for x in res]
    return res


lin = np.linspace(0, 1, dtype=float, num=1000)
fx = [func(x) for x in lin]
tp = []

for i in range(POWER):
    tp.append(top(i, fx))

plt.figure(figsize=(12, 12))
plt.plot(lin, lin, label="diag")


for i in range(POWER):
    plt.plot(lin, tp[i], label=i)
plt.legend()
plt.xlabel(f"power={POWER}")
plt.show()

tp_line = []
for i in range(POWER):
    tp_line.append([(x > 0) * (POWER - i) for x in tp[i]])

plt.figure(figsize=(12, 12))


for i in range(POWER):
    plt.plot(lin, tp_line[i], label=i)
plt.legend()
plt.xlabel(f"power={POWER}")
plt.show()
