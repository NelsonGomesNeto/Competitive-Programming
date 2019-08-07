#include <bits/stdc++.h>

int main()
{
  int n, e; scanf("%d %d", &n, &e);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  bool can = false;
  for (int i = 0; i < n; i ++)
    for (int j = i + 1; j < n; j ++)
      if (a[i] + a[j] == e)
        can = true;
  printf("%s\n", can ? "SIM" : "NAO");
  return(0);
}