import numpy as np
from scipy.integrate import simps
def f(x):
    return x**3


x = np.linspace(1.0, 4.0, 20)
y = f(x)
a = simps(y,x)

x = np.linspace(1.0, 4.0, 19)
y = f(x)
b = simps(y,x)

print ("%.4f  %.4f" %(a, b))
