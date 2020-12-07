#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int height = 0, sum = 1, i;
  while (n)
  {
    for (i = 0; i < sum && n; i ++, n --);
    if (i == sum) { height ++; sum += height + 1; }
  }
  printf("%d\n", height);
  return(0);
}