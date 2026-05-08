#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  A graph is bipartite if you can divide into two sets of vertices, where every
  edge has vertices from different sets.

  For any two numbers A and B, they meet in lcm(A, B). For the graph to be bipartite,
  A and B must meet in the same parity of steps (A.steps and B.steps even or odd).
  We can rephrase that as "A.steps + B.steps must be even". Steps are calculated
  this way: A.steps = lcm(A, B) / A and B.steps = lcm(A, B) / B.

  Suppose A = 2^x * a, B = 2^y * b. lcm(A, B) = 2^(max(x, y)) * c
    (Remember that lcm(A, B) = A * B / gcd(A, B))
  If x > y:
    A.steps = lcm(A, B) / A = 2^(x - x) * e, which is even
    B.steps = lcm(A, B) / B = 2^(x - y) * f, which is odd
  If y > x:
    A.steps = lcm(A, B) / A = 2^(y - x) * e, which is odd
    B.steps = lcm(A, B) / B = 2^(y - y) * f, which is even
  In both cases: even + odd == odd
  So, if x != y: the graph can't be bipartite.

  Now, we just need to find the biggest group with the same power of two (as a divisor)
  and remove all the other groups.

  There's a much easier way to visualize this:
    (2^x * a) + (2^x * b) The lowest bit flips (the bit in the x-th position)
    Imagine this as changing the side in the bipartite graph
    If A and B shares the same power of two as divisor:
      They will flip side in synchrony
    Else:
      They flip out of sync and will eventually meet on different sides
*/

const int maxN = 2e5; int n;
lli b[maxN];
list<lli> groups[64];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < 64; i ++) groups[i].clear();

    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &b[i]);
      lli p = 0; while (b[i] % (1LL << (p + 1)) == 0) p ++;
      groups[p].push_back(b[i]);
    }

    int best = 0;
    for (int i = 1; i < 64; i ++)
      if (groups[i].size() > groups[best].size())
        best = i;
    printf("%d\n", (int) (n - groups[best].size()));
    for (int i = 0, first = true; i < 64; i ++)
      if (i != best)
        for (lli j: groups[i])
        {
          if (first) printf("%lld", j);
          else printf(" %lld", j);
          first = false;
        }
    if (n - groups[best].size()) printf("\n");
  }
  return(0);
}