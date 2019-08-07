#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i ++) printf("%d%c", a[i] - !(a[i] & 1), i < n - 1 ? ' ' : '\n');
  return(0);
}
