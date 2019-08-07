#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  int a[n], give;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &give);
    a[give - 1] = i + 1;
  }

  for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  
  return(0);
}