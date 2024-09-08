#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool checkPrime(int x, int i, int sqx)
{
  if (x % i == 0) return false;
  if (i > sqx) return true;
  return checkPrime(x, i + 1, sqx);
}
bool isPrime(int x) { return checkPrime(x, 2, sqrt(x)); }

int fibonacci(int n)
{
  if (n <= 1) return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

bool checkFibonacci(int x, int n)
{
  int fibn = fibonacci(n);
  if (fibn >= x) return fibn == x;
  return checkFibonacci(x, n + 1);
}

bool isFibonacci(int x) { return checkFibonacci(x, 0); }

int score(int x)
{
  bool isPrimeNumber = isPrime(x);
  bool isFibonacciNumber = isFibonacci(x);
  if (isPrimeNumber && isFibonacciNumber) return 3;
  else if (isPrimeNumber || isFibonacciNumber) return 1;
  return 0;
}

void solve(int n)
{
  if (n == 0) return;
  int x, y;
  scanf("%d %d", &x, &y);

  int kcajScore = score(x), ordepScore = score(y);
  if (kcajScore > ordepScore || (kcajScore == ordepScore && x > y)) printf("Kcaj\n");
  else printf("Ordep\n");

  solve(n - 1);
}

int main()
{
  int n;
  scanf("%d", &n);
  solve(n);
  return 0;
}