#include <bits/stdc++.h>
int dm[7] = {100, 50, 20, 10, 5, 2, 1};

int main()
{
  int n, prev; scanf("%d", &n); prev = n;

  int needed[7]; memset(needed, 0, sizeof(needed));
  for (int k = 0; k < 7; k ++)
  {
    needed[k] += n / dm[k];
    n %= dm[k];
  }

  printf("%d\n", prev);
  for (int k = 0; k < 7; k ++)
    printf("%d nota(s) de R$ %d,00\n", needed[k], dm[k]);
}
