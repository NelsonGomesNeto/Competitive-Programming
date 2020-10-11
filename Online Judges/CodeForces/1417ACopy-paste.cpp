#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, k;
int a[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);
      for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

      priority_queue<int, vector<int>, greater<int>> pq;
      for (int i = 0; i < n; i++)
        pq.push(a[i]);

      int ans = 0;
      while (pq.size() > 1)
      {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        if (a + b > k) break;
        pq.push(a + b); pq.push(a);
        ans++;
      }
      printf("%d\n", ans);
    }

  return 0;
}
