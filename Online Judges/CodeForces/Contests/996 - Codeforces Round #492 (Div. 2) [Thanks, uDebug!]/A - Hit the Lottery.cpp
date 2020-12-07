#include <bits/stdc++.h>
int c[5] = {100, 20, 10, 5, 1};

int main()
{
  int n; scanf("%d", &n);

  int bills = 0;
  for (int k = 0; k < 5; k ++)
  {
    bills += n / c[k];
    n %= c[k];
  }

  printf("%d\n", bills);
  return(0);
}