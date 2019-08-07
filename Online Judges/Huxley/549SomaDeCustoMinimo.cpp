#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n, seed, a, b, c;
  while (scanf("%d %d %d %d %d", &n, &seed, &a, &b, &c) != EOF)
  {
    priority_queue<lli, vector<lli>, greater<lli> > pq;
    pq.push(seed); lli prev = seed;
    for (int i = 1; i < n; i ++)
    {
      lli next = (prev * a + b) % c;
      pq.push(next);
      prev = next;
    }

    lli sum = 0, cost = 0;
    lli n1, n2;
    while (!pq.empty())
    {
      n1 = n2 = 0;
      n1 = pq.top(); pq.pop();
      if (!pq.empty())
      {
        n2 = pq.top(); pq.pop();
      }
      cost += n1 + n2;
      sum = n1 + n2;
      if (!pq.empty()) pq.push(n1 + n2);
    }
    printf("%lld %lld\n", sum, n > 1 ? cost : 0);
  }
  return(0);
}