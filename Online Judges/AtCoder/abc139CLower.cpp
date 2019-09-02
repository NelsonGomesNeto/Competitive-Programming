#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int h[maxN];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &h[i]);

  int ans = 0;
  for (int i = 1, now = 0; i < n; i ++)
  {
    if (h[i] > h[i - 1])
      now = 0;
    else
      now ++;
    ans = max(ans, now);
  }
  printf("%d\n", ans);

  return(0);
}