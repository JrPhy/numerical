There are many methods for integration, simpson's method is most widely used, 
so I just provide simpson's code. but introduce other mathods for integration.

#Note: If you integrate in polar or somespace with angle, remember to transform to degree to rad.

#Note: In scipy, it uses 1/3 rule for simpson, it just apply for odd number of point.
       For even, it uses trapezoid method, so the error is higher.
       
Try the script below:

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
