#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
int dist[maxN];
set<int> positions;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    positions.clear();
    int distSum = 0, eqSize;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &dist[i]);
      positions.insert(distSum);
      distSum += dist[i];
    }

    if (distSum % 3 != 0) printf("0\n");
    else
    {
      eqSize = distSum / 3;
      int now = 0, ans = 0;
      for (int i = 0; i < n; i ++)
      {
        if (now >= eqSize) break;
        if (positions.count(now + eqSize) && positions.count(now + 2*eqSize))
          ans ++;
        now += dist[i];
      }
      printf("%d\n", ans);
    }
  }
  return(0);
}