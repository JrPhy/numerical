int Fibonacci(int n)
{
	int i, F[n+1];
	F[0] = 1;F[1] = 1;
	for(i=2;i<n+1;i++) F[i] = F[i-1] + F[i-2];
	return F[n];
}
