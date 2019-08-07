#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n; scanf("%d", &n);
  int a[n], small = 1<<20;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    small = min(small, a[i]);
  }
  sort(a, a+n);

  int blocks = 0;
  for (int i = 1; i <= n; i ++)
  {
    int can = 1;
    for (int j = 0; j < i; j ++)
    {
      int now = 1 << 20;
      for (int at = n - j - 1; at >= 0; at -= i)
      {
        now = min(now - 1, a[at]);
        if (now < 0) can = 0;
      }
    }
    blocks = i;
    if (can) break;
  }
  printf("%d\n", blocks);

  return(0);
}