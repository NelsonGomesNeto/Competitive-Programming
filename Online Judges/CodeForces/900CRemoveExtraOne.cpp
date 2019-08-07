#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int a[n], record[n], prev = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    if (a[i] > prev)
    {
      prev = a[i];
      record[i] = 1;
    }
  }

  int smallest = 1e9;
  for (int i = 0; i < n; i ++)
  {
    if (!record[i] && a[i] < smallest)
      smallest = a[i];
  }

  printf("%d\n", smallest == 1e9 ? 1 : smallest);

  return(0);
}