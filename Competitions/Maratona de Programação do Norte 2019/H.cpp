#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 1e3, maxH = 1e6; int n;
int h[maxN];

int inc[maxN], decr[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++) scanf("%d", &h[i]);

  for (int i = 0; i < n; i ++)
  {
    inc[i] = 1, decr[n - i - 1] = 1;
    for (int j = i - 1; j >= 0; j --)
    {
      if (h[i] > h[j])
        inc[i] = max(inc[i], inc[j] + 1);
      if (h[n - i - 1] > h[n - j - 1])
        decr[n - i - 1] = max(decr[n - i - 1], decr[n - j - 1] + 1);
    }
  }
  DEBUG {
    for (int i = 0; i < n; i ++)
      printf("%d%c", inc[i], i < n - 1 ? ' ' : '\n');
    for (int i = 0; i < n; i ++)
      printf("%d%c", decr[i], i < n - 1 ? ' ' : '\n');
  }

  int ans = 0;
  for (int i = 0; i < n; i ++) ans = max(ans, inc[i] + decr[i]);
  printf("%d\n", ans);

  return(0);
}