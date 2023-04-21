# Построить графики степеней треугольного отображения
# Рассмотреть случай r<1/2, r>1/2, r=1/2

import numpy as np
import matplotlib.pyplot as plt

R = 0.6
POW = 7

def func(x: float) -> float:
    return 2 * R * x if x < 0.5 else 2 * R * (1 - x)

def top(points):
    res = points
    for i in range(POW):
        res = [func(x) for x in res]
    return res

lin = np.linspace(0, 1, dtype=float, num=1000)
fx = [func(x) for x in lin]
tp = top(fx)

plt.figure(figsize=(5, 5))
plt.plot(lin, lin, label="diag")
plt.plot(lin, fx, label="f(x)")
plt.plot(lin, tp, label="f1(x)")
plt.legend()
plt.xlabel(f"pow={POW}, r={R}")

plt.show()
