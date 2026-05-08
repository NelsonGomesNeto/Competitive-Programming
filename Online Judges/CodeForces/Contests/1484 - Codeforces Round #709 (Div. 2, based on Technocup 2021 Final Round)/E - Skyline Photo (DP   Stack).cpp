#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
const lli inf = 1e16;
int h[maxN + 1];
lli b[maxN];
lli ans[maxN + 1], acc[maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &h[i]);
      h[i]--;
    }
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    /*
      ans = closestSmaller[i] == n ? b[i] : solve(closestSmaller[i]);
      ans = max(ans, segtree.query(i + 1, closestSmaller[i]).value + b[i]);
    */
    h[n] = -1e6, acc[n] = 0, ans[n] = -inf;
    stack<int> s;
    s.push(n);
    for (int i = n - 1; i >= 0; i--)
    {
      lli curr = -inf;
      while (h[i] < h[s.top()])
      {
        curr = max(curr, acc[s.top()]);
        s.pop();
      }
      acc[s.top()] = max(acc[s.top()], curr);

      ans[i] = acc[s.top()] + b[i];
      ans[i] = max(ans[i], ans[s.top()]);

      acc[i] = ans[i];
      s.push(i);
      DEBUG printf("\t%d (%d, %lld) - %lld || %lld | %lld\n", i, h[i], b[i], ans[i], acc[s.top()], curr);
    }
    printf("%lld\n", ans[0]);
  }
  return 0;
}