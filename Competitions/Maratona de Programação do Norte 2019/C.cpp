#include <bits/stdc++.h>
using namespace std;

int main()
{
  int p, c, n; scanf("%d %d %d", &p, &c, &n);
  int vic[n];
  for (int i = 0; i < n; i ++) scanf("%d", &vic[i]);

  int ans = 0, weight = min(vic[0], p + c);
  for (int i = 0; i < n - 1; i ++)
  {
    if (vic[i + 1] < p) break;
    if (vic[i + 1] < weight)
      ans ++, weight = vic[i + 1];
  }
  printf("%d\n", ans);
  return(0);
}