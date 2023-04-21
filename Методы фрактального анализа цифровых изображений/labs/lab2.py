# Построить приближение к стандартному множеству Кантора используя треугольное отображение (r=3)


import numpy as np
import matplotlib.pyplot as plt

N = 6
LINEWIDTH = 7
fig, ax = plt.subplots(figsize=(8, 6))

def getKant(begin, end, step=0):
    if step < N:
        step += 1
        t = (end - begin) / 3
        ax.hlines(step, begin, begin+t, 'purple', linewidth=LINEWIDTH)
        ax.hlines(step, begin + t * 2, end, 'purple', linewidth=LINEWIDTH)
        return getKant(begin, begin + t, step), getKant(begin + t * 2, end, step)


ax.hlines(0, 0, 1, 'purple', linewidth=LINEWIDTH)
lines = getKant(0, 1)

plt.show()
