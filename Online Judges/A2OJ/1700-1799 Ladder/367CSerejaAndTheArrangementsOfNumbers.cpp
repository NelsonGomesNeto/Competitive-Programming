#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We can represent a beautiful array as an graph
    That graph will be either a complete graph or a semi-eulerian graph
    Since every vertex (number) must be connected somehow AND there must be a
    path in which we use every edge once (Also known as Eulerian Path).
      Complete graphs with an odd number of vertices has 0 odd
      degree vertices: Eulerian Cycle.
      Complete graphs with an even number of vertices has n odd
      degree vertices: we can't build an Eulerian Path (nor a Cycle). So we
      add n / 2 - 1 vertices, connecting pair of vertices with odd degree
      and leaving a pair. This way we will can make an Eulerian Path. Notice
      that we could add another vertice and make an Eulerian Cycle; but that
      wouldn't minimize the amount of added vertices.

  So, we upper boundly binary search for the maximum amount of cupons we can
  buy and still make an Eulerian Cycle or Path.
  An array of size n has n - 1 edges (a1 - a2, a2 - a3, ..., an-1 - an).
  So, with that amount of edges: could we build an Eulerian Cycle or Path?
*/

const int maxN = 2e6, maxM = 1e5; int n, m;
struct Cupom
{
  lli q, w;
  bool operator<(const Cupom &other) const
  {
    return w > other.w;
  }
};
Cupom cupons[maxM];

lli required(int vertices)
{
  if (vertices & 1)
    return (lli) vertices * (vertices - 1) >> 1LL;
  return ((lli) vertices * (vertices - 1) >> 1LL) + (vertices >> 1) - 1;
}

int binarySearch(int edges)
{
  int lo = 1, hi = m;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (required(mid) <= (lli) edges) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < m; i ++)
      scanf("%lld %lld", &cupons[i].q, &cupons[i].w);
    sort(cupons, cupons+m);

    int canUse = binarySearch(n - 1);
    lli ans = 0;
    for (int i = 0; i < canUse; i ++)
      ans += cupons[i].w;
    printf("%lld\n", ans);
  }
  return 0;
}