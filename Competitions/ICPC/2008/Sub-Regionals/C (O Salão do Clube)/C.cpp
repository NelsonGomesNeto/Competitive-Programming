#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 1e5, maxX = 1e4, inf = 1e9; int n, m, l, k;
int planks[maxK], plankCount[maxX + 1], countCopy[maxX + 1];

int main()
{
  while (scanf("%d %d %d %d", &n, &m, &l, &k) != EOF && !(!n && !m))
  {
    memset(plankCount, 0, sizeof(plankCount));
    for (int i = 0; i < k; i ++)
    {
      scanf("%d", &planks[i]);
  	  plankCount[planks[i]] ++;
    }
    memcpy(countCopy, plankCount, sizeof(countCopy));
    sort(planks, planks+k); reverse(planks, planks+k);

    int ans = inf;
    // Vertical fill
      int used = min(plankCount[n], m*100 / l);
      if (m*100 % l == 0)
        for (int i = plankCount[n]*l, at = n - 1; i < m*100;)
        {
          if (plankCount[at] && (at != n - at ? plankCount[n - at] : plankCount[n - at] - 1))
            used += 2, i += l, plankCount[at] --, plankCount[n - at] --;
          else
            at --;
          if (at < 1) { used = inf; break; }
        }
      else
        used = inf;
      ans = min(ans, used);
    // Horizontal fill
      memcpy(plankCount, countCopy, sizeof(plankCount));
      used = min(plankCount[m], n * 100 / l);
      if (n*100 % l == 0)
        for (int i = plankCount[m]*l, at = m - 1; i < n*100;)
        {
          if (plankCount[at] && (at != m - at ? plankCount[m - at] : plankCount[m - at] - 1))
            used += 2, i += l, plankCount[at] --, plankCount[m - at] --;
          else
            at --;
          if (at < 1) { used = inf; break; }
        }
      else
        used = inf;
      ans = min(ans, used);

    if (ans == inf) printf("impossivel\n");
    else printf("%d\n", ans);
  }
  return(0);
}