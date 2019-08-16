When you use int to store the Fibonacci number, it’s bigger than 2^32 -1 as n = 48,
so it must use big number algorithm.
GMP is one of the solution for this issue, 
you can google it and build the environment to get all digit when n is bigger than 48.
