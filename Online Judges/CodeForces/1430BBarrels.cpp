#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
lli a[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);
      priority_queue<lli> pq;
      for (int i = 0; i < n; i++)
      {
        scanf("%lld", &a[i]);
        pq.push(a[i]);
      }

      while (k--)
      {
        lli last = pq.top();
        pq.pop();
        lli secondLast = pq.top();
        pq.pop();
        pq.push(last + secondLast), pq.push(0);
      }
      lli biggest = pq.top();
      lli smallest = pq.top();
      while (!pq.empty())
      {
        smallest = pq.top();
        pq.pop();
      }
      printf("%lld\n", biggest - smallest);
    }
  return 0;
}
