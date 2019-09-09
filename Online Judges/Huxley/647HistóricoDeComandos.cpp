#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n;
int p[maxN];
map<int, int> pos;

int main()
{
  while (scanf("%d", &n) && n)
  {
    pos.clear();
    int ans = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &p[i]);
      if (pos.count(p[i]))
        ans += min(p[i] + i, i - pos[p[i]]);
      else
        ans += p[i] + i;
      pos[p[i]] = i;
    }
    printf("%d\n", ans);
  }
  return(0);
}