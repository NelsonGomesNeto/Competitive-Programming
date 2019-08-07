#include <bits/stdc++.h>
int isFib[(int) 1e6];

int fib(int n)
{
  if (n <= 1) return(1);
  int ans = fib(n - 1) + fib(n - 2);
  isFib[ans] = 1;
  return(ans);
}

void print(int i, int n)
{
  if (i > n) return;
  printf("%c", isFib[i] ? 'O' : 'o');
  print(i + 1, n);
}

int main()
{
  memset(isFib, 0, sizeof(isFib));
  int n; scanf("%d", &n);
  fib(16); isFib[1] = isFib[2] = 1;
  print(1, n); printf("\n");
  return(0);
}