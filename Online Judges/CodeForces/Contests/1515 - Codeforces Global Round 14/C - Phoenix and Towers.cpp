#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m, x;
int h[maxN];
int ans[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 0; i < n; i++)
      scanf("%d", &h[i]);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (int i = 0; i < m; i++) pq.push({0, i});

    for (int i = 0; i < n; i++)
    {
      int height = pq.top().first, j = pq.top().second; pq.pop();
      ans[i] = j + 1;
      pq.push({height + h[i], j});
    }

    printf("YES\n");
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
