#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3 + 1; int n;
char path[maxN + 2];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int x, y; scanf("%d %d %s", &x, &y, path);
    x += 1000, y += 1000;
    int sx = 1000, sy = 1000, size = strlen(path);
    int ans = 1e9;
    path[size] = 'k', path[size + 1] = '\0';
    for (int i = 0; path[i]; i++)
    {
      int dist = abs(y - sy) + abs(x - sx);
      if (dist <= i) ans = min(ans, i);
      if (path[i] == 'N') y++;
      else if (path[i] == 'S') y--;
      else if (path[i] == 'E') x++;
      else if (path[i] == 'W') x--;
    }

    printf("Case #%d: ", tt);
    if (ans == 1e9) printf("IMPOSSIBLE\n");
    else printf("%d\n", ans);
  }
  return 0;
}