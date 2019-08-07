#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5, maxP = 1e4; int n, k;
int p[maxN];

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    int ans = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &p[i]);
      ans += p[i];
    }

    priority_queue<int> pq;
    for (int i = n - 1; i >= 0; i --)
    {
      pq.push(p[i]);
      if (i % (k + 1) == k) { ans -= pq.top(); pq.pop(); }
    }

    printf("%d\n", ans);
  }

  return(0);
}