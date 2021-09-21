from scipy.integrate import simps
import random
import numpy as np
import matplotlib.pyplot as plt


def mysimps(y, x=None, dx=1, axis=-1):
    '''
    Integrate y(x) using samples along the given axis and the composite
    Simpson's rule. This method needs at least 3 point, so if the number
    of point is 2, then it uses trapezoidal rule.

    Parameters
    ----------
    y : array_like
        Array to be integrated.
    x : array_like, optional
        If given, the points at which `y` is sampled.

    See Also
    --------
    quad: adaptive quadrature using QUADPACK
    romberg: adaptive Romberg quadrature
    quadrature: adaptive Gaussian quadrature
    fixed_quad: fixed-order Gaussian quadrature
    dblquad: double integrals
    tplquad: triple integrals
    romb: integrators for sampled data
    cumtrapz: cumulative integration for sampled data
    ode: ODE integrators
    odeint: ODE integrators

    Examples
    --------
    >>> from scipy import integrate
    >>> x = np.arange(0, 10)
    >>> y = np.arange(0, 10)
    >>> integrate.simps(y, x)
    40.5
    >>> y = np.power(x, 3)
    >>> integrate.simps(y, x)
    1640.25
    '''
    n = len(y)
    count = 0
    for i in range(2, n):
        if abs((x[i-2] - x[i-1]) - (x[i-1] - x[i])) < 1e-8:
            count = count + 1
    if x is not None:
        if count != n-2:
            flag = 0
        else:
            flag = 1
            
    
    if x is not None and count != n-2:

        if len(x) != len(y):
            raise ValueError("len (x) must be the same as len (y)")
        if n <= 1:
            result = 0

        elif n == 2:
            result = 0.5*(x[1] - x[0])*(y[0] + y[1])

        elif (n-1) % 2 == 0:
            result = 0
            for i in range(0, len(y) - 2, 2):
                d10 = x[i+1] - x[i]
                d21 = x[i+2] - x[i+1]
                d20 = d21 + d10
                slope10 = (y[i+1] - y[i])/d10
                slope21 = (y[i+2] - y[i+1])/d21
                braket210 = (slope21 - slope10)/d20
                result += (y[i]*d20 + (d20*d20*slope10/2)
                          + 0.5*braket210*(d20*d21*d21 - d21**3/3 - d10**3/3))

        elif (n-1) % 3 == 0:
            result = 0
            for i in range(0, len(y) - 3, 3):
                d10 = x[i+1] - x[i]
                d21 = x[i+2] - x[i+1]
                d32 = x[i+3] - x[i+2]
                d20 = d21 + d10
                d31 = d32 + d21
                d30 = d32 + d21 + d10
                slope10 = (y[i+1] - y[i])/d10
                slope21 = (y[i+2] - y[i+1])/d21
                slope32 = (y[i+3] - y[i+2])/d32
                braket210 = (slope21 - slope10)/d20
                braket321 = (slope32 - slope21)/d31
                braket3210 = (braket321 - braket210)/d30
                result += (y[i]*d30 + (d30*d30*slope10/2)
                          + 0.5*braket210*(d30*d31*d31 - d31**3/3 - d10**3/3)
                          + 0.5*braket3210*(d30*d31*d32*d32 - d31*d32*d32*d32/3
                                       + d10*d20*d20*d20/3)
                                       + d32**4/12 - d20**4/12)

        else:
            
            result = 0
            for i in range(0, len(y) - 4, 2):
                d10 = x[i+1] - x[i]
                d21 = x[i+2] - x[i+1]
                d20 = d21 + d10
                slope10 = (y[i+1] - y[i])/d10
                slope21 = (y[i+2] - y[i+1])/d21
                braket210 = (slope21 - slope10)/d20
                result += (y[i]*d20 + (d20*d20*slope10/2)
                          + 0.5*braket210*(d20*d21*d21 - d21**3/3 - d10**3/3))

            d10 = x[n-3] - x[n-4]
            d21 = x[n-2] - x[n-3]
            d32 = x[n-1] - x[n-2]
            d20 = d21 + d10
            d31 = d32 + d21
            d30 = d32 + d21 + d10
            slope10 = (y[n-3] - y[n-4])/d10
            slope21 = (y[n-2] - y[n-3])/d21
            slope32 = (y[n-1] - y[n-2])/d32
            braket210 = (slope21 - slope10)/d20
            braket321 = (slope32 - slope21)/d31
            braket3210 = (braket321 - braket210)/d30

            result += (y[n-4]*d30 + (d30*d30*slope10/2)
                      + 0.5*braket210*(d30*d31*d31 - d31**3/3 - d10**3/3)
                      + 0.5*braket3210*(d30*d31*d32*d32 - d31*d32*d32*d32/3
                                   + d10*d20*d20*d20/3)
                                   + d32**4/12 - d20**4/12)
        return result

    else:
        h = x[1] - x[0]
        y1 = 0
        y2 = 0
        if n <= 1:
            result = 0

        elif n == 2:
            result = 0.5*h*(y[0]+y[1])

        elif (n-1) % 2 == 0:
            for i in range(1, len(y) - 1):
                if i % 2 == 0:
                    y1 = y1 + y[i]
                else:
                    y2 = y2 + y[i]
            result = h*(y[0]+2*y1+4*y2+y[n-1])/3

        elif (n-1) % 3 == 0:
            for i in range(1, len(y) - 1):
                if i % 3 == 0:
                    y1 = y1 + y[i]
                else:
                    y2 = y2 + y[i]
            result = 3*h*(y[0]+2*y1+3*y2+y[n-1])/8

        else:
            for i in range(1, len(y) - 4):
                if(i % 2 == 0):
                    y1 = y1 + y[i]
                else:
                    y2 = y2 + y[i]
            result = (h*(y[0] + 2*y1 + 4*y2 + y[n-4])/3 +
                      3*h*(y[n-4] + 3*y[n-3] + 3*y[n-2] + y[n-1])/8)
        return result


# slice non-equally
for j in range(1, 70):
    x = []
    y = []
    x.append(0)
    for i in range(0, j):
        x.append(random.uniform(0, 4))
    x.append(4)
    x = sorted(x)
    for i in range(0, len(x)):
        y.append(x[i]**3)
    print("%d  %.6f  %.6f" % (len(x), simps(y, x), mysimps(y, x)))
'''

# slice equally
for j in range(3, 270):
    x = []
    y = []
    x = np.linspace(0,4,j)
    for i in range(0, len(x)):
        y.append(x[i]**3)
    print("%d  %.6f  %.6f" % (len(x), simps(y, x), mysimps(y, x)))
'''
#plt.plot(x, y)