# Построить приближение к инвариантному множеству отображения f(z)=, где с, комплексный параметр.
#
#import numpy as np
#import matplotlib.pyplot as plt
#
#julia_C = 0.383 + 0.13j
#
#def julia_set(x, y):
#    z = np.array(x + 1j * y)
#    r = np.zeros(z.shape)
#    m = np.ones(z.shape, dtype=bool)
#    for i in range(24):
#        z[m] = z[m] ** 2 + julia_C
#        m = np.abs(z) < 2
#        r += m
#    return r
#
#def complex_str(c):
#    return np.array_str(np.array([julia_C]), suppress_small=True, precision=3)
#
#
#def grid(width, offset, n):
#    x = np.linspace(-width + offset, width + offset, n)
#    y = np.linspace(-width, width, n)
#    return np.meshgrid(x, y), (x.min(), x.max(), y.min(), y.max())

#
#fig, (bx) = plt.subplots(1, 1)
#
#bx.set_title("Julia Set")
#
#(X, Y), extent = grid(2, 0, 1000)
#julia = julia_set(X, Y)
#img = bx.imshow(julia, extent=extent, cmap="gray")
#
#plt.tight_layout()
#plt.show()


# Построить Хeнон

import numpy as np
import matplotlib.pyplot as plt
plt.style.use('dark_background')

def henon_attractor(x, y, a=1.4, b=0.3):
    '''Computes the next step in the Henon
    map for arguments x, y with kwargs a and
    b as constants.
    '''
    x_next = 1 - a * x ** 2 + y
    y_next = b * x
    return x_next, y_next
    
# Количество итераций
steps = 100000
X = np.zeros(steps + 1)
Y = np.zeros(steps + 1)

# Начальная точка
X[0], Y[0] = 0, 0

# Добавляем точки в массив
for i in range(steps):
    x_next, y_next = henon_attractor(X[i], Y[i])
    X[i+1] = x_next
    Y[i+1] = y_next
    

plt.plot(X, Y, '^', color='white', alpha = 0.8, markersize=0.3)
plt.axis('off')
plt.show()
plt.close()
