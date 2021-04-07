#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
struct Node
{
  lli r, c;
  bool operator<(const Node &other) const { return r < other.r; }
};
Node nodes[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &nodes[i].r);
    for (int i = 0; i < n; i++)
      scanf("%lld", &nodes[i].c);
    sort(nodes, nodes+n);
    DEBUG
      for (int i = 0; i < n; i++)
        printf("\t%lld %lld\n", nodes[i].r, nodes[i].c);

    lli ans = 0;
    Node curr = {1, 1};
    for (int i = 0; i < n; i++)
    {
      if (curr.r == nodes[i].r && curr.c == nodes[i].c)
        continue;

      if ((curr.r + curr.c) & 1)
      {
        // -> r + 1, c + 1
        /*
          2, 1
          3, 2
          4, 3
        */
        lli r = nodes[i].r - curr.r;
        lli c = nodes[i].c - curr.c;
        ans += (r - c + 1) >> 1;
      }
      else
      {
        lli r = nodes[i].r - curr.r;
        lli c = nodes[i].c - curr.c;
        if (r == c)
          ans += r;
        else
        {
          // lli rr = nodes[i].r - c;
          lli newR = curr.r;
          lli deltaR = nodes[i].r - newR;
          ans += (deltaR - c) >> 1;
        }
      }

        // -> r + 1
        // lli r = nodes[i].r - curr.r;
        // lli c = nodes[i].c - curr.c;
        // lli freeR = 2 * c;
        // lli freeR2 = freeR + 1;
        // printf("\teven: %lld %lld | %lld %lld | %lld %lld %lld\n", curr.r, curr.c, nodes[i].r, nodes[i].c, freeR, freeR2, r);
        // ans += min(abs(r - freeR2), abs(r - freeR));
      DEBUG printf("\t\t(%lld, %lld) -> (%lld, %lld) %lld\n", curr.r, curr.c, nodes[i].r, nodes[i].c, ans);

      curr = nodes[i];
    }
    printf("%lld\n", ans);
  }
  return 0;
}
