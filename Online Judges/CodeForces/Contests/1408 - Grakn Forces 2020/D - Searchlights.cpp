#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  robbers: (rx, ry)
  searchlights: (sx, sy)

  safe with (dx, dy), if for all robbers:
    1 - rx + dx > sx
      |or|
    2 - ry + dy > sy

  Bruteforce:
    (test every possible dx)
    for dx in [0 : maxX]:
      (calculate the required dy for this dx)
      requiredDy = 0
      for r in robbers:
        for s in searchlights:
          if rx + dx <= sx: // must be safe by rule 2
            requiredDy = max(requiredDy, sy - ry + 1)
    (ans is min(dx + requiredDy))

  Notice that:
    rx + dx <= sx is true for all DX <= dx
    and sy - ry + 1 isn't dependent on dx, so:
    So a requiredDy of sy - ry + 1 will happend for every DX <= dx

  Accumulate it ftw:
    requiredY[maxX] = all 0s

    for r in robbers:
      for s in searchlights:
        firstDx = sx - rx // from this dx to the left: you will require dy
        requiredDy[firstDx] = max(requiredDy[firstDx], sy - ry + 1)

    for dx in [maxX : 0]: // notice that it's reversed
      requiredDy[dx] = max(requiredDy[dx] requriedDy[dx + 1])

    O(n * m + maxX) ftw
*/

const int maxN = 2e3, maxX = 1e6 + 1; int n, m;
const int inf = 1e7;
struct Point
{
  int x, y;
  void read() { scanf("%d %d", &x, &y); }
};
Point r[maxN], s[maxN];
int requiredY[maxX];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      r[i].read();
    for (int i = 0; i < m; i++)
      s[i].read();

    memset(requiredY, 0, sizeof(requiredY));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[j].x >= r[i].x)
        {
          int xDelta = s[j].x - r[i].x;
          int reqY = s[j].y - r[i].y + 1;
          requiredY[xDelta] = max(requiredY[xDelta], reqY);
        }

    for (int i = maxX - 2; i >= 0; i--)
      requiredY[i] = max(requiredY[i], requiredY[i + 1]);

    int ans = inf;
    for (int x = 0; x < maxX; x++)
      ans = min(ans, x + requiredY[x]);

    printf("%d\n", ans);
  }
  return 0;
}