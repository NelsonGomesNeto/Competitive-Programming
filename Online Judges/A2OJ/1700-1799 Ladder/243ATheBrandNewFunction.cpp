#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e5, maxBit = 20, maxX = (1 << 20) + 1; int n;
int a[maxN]; bool has[maxX];
int closestLeft[maxBit][maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    for (int j = 0; j < maxBit; j ++)
      if (a[i] & (1 << j))
        closestLeft[j][i] = i;
      else
        closestLeft[j][i] = i ? closestLeft[j][i - 1] : -1;
  }
  DEBUG for (int j = 0; j < maxBit; j ++)
    for (int i = 0; i < n; i ++)
      printf("%d%c", closestLeft[j][i], i < n - 1 ? ' ' : '\n');

  for (int i = n - 1; i >= 0; i --)
  {
    int now = a[i], at = i, closest;
    while (1)
    {
      has[now] = true, closest = -1;
      for (int j = 0; j < 20; j ++)
        if (!(now & (1 << j)))
          closest = max(closest, closestLeft[j][at]);
      if (closest == -1)
        break;
      now |= a[closest], at = closest;
    }
  }

  int ans = 0;
  for (int i = 0; i < maxX; i ++) ans += has[i];
  printf("%d\n", ans);

  return 0;
}