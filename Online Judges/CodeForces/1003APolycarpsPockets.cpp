#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, a[101], x, ans = 1; scanf("%d", &n);
  memset(a, 0, sizeof(a));
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &x);
    a[x] ++;
    ans = max(ans, a[x]);
  }
  printf("%d\n", ans);
  return(0);
}