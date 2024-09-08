#include <stdio.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimization("unroll-loops, no-stack-protector")
#pragma GCC target("avx,avx2,fma")

#define MAXN 100005

int v[MAXN];

int main()
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &v[i]);
  int q;
  scanf("%d", &q);
  while (q--)
  {
    int c;
    scanf("%d", &c);
    if (c == 1)
    {
      int i, j;
      scanf("%d %d", &i, &j);
      i--, j--;
      int aux = v[i];
      v[i] = v[j];
      v[j] = aux;
    }
    else if (c == 2)
    {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      l--, r--;
      int ans = 1e9;
      for (int i = l; i <= r; i++)
      {
        if (v[i] >= x && v[i] < ans)
          ans = v[i];
      }
      (ans == 1e9) ? printf("-1\n") : printf("%d\n", ans);
    }
    else
    {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      l--, r--;
      int ans = -1;
      for (int i = l; i <= r; i++)
      {
        if (v[i] <= x && v[i] > ans)
          ans = v[i];
      }
      (ans == -1) ? printf("-1\n") : printf("%d\n", ans);
    }
  }
}