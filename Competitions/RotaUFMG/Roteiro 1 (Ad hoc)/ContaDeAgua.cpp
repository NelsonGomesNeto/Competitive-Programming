#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  
  int cost = 0;
  if (n <= 10)
    cost += 7;
  else if (n <= 30)
    cost += 7 + (n - 10) * 1;
  else if (n <= 100)
    cost += 7 + 20 + (n - 30) * 2;
  else
    cost += 7 + 20 + 140 + (n - 100) * 5;

  printf("%d\n", cost);

  return(0);
}