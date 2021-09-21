There are many methods for integration, simpson's method is most widely used, 
so I just provide simpson's code. but introduce other mathods for integration.

#Note: If you integrate in polar or somespace with angle, remember to transform to degree to rad.

#Note: In scipy, it uses 1/3 rule for simpson, it just apply for odd number of point.
       For even, it uses trapezoid method, so the error is higher.
       
Try the script in testScipy

The normal Simpson's method implement with equally spaced dx, as dx is not equally spaced, there is complicate version of Simpson's method by taylor expansion.\
https://www.researchgate.net/publication/317339672_Numerical_Integration_Schemes_for_Unequal_Data_Spacing
