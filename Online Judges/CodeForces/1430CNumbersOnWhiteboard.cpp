#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      priority_queue<int, vector<int>, less<int>> pq;
      for (int i = 1; i <= n; i++)
        pq.push(i);

      vector<pair<int, int>> ops;
      while (pq.size() > 1)
      {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();

        pq.push((a + b + 1) >> 1);
        ops.push_back({a, b});
      }

      printf("%d\n", pq.top());
      for (auto &p: ops)
        printf("%d %d\n", p.first, p.second);
    }
  return 0;
}
