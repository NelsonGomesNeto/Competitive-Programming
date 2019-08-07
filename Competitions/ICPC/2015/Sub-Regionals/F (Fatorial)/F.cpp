#include <bits/stdc++.h>
using namespace std;

int main()
{
  int f[10]; f[0] = 1;
  for (int i = 1; i < 10; i ++) f[i] = i * f[i - 1];

  int n; scanf("%d", &n);

  int ans = 0;
  for (int i = 9; i >= 1 && n; i --)
  {
    int k = n / f[i];
    ans += k, n -= k * f[i];
  }
  printf("%d\n", ans);

  return(0);
}