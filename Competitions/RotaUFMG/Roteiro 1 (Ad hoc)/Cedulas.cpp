#include <bits/stdc++.h>
int dc[7] = {100, 50, 20, 10, 5, 2, 1};

int main()
{
  int n; scanf("%d", &n);

  printf("%d\n", n);
  for (int i = 0; i < 7; i ++)
  {
    printf("%d nota(s) de R$ %d,00\n", n / dc[i], dc[i]);
    n -= (n / dc[i]) * dc[i];
  }

  return(0);
}