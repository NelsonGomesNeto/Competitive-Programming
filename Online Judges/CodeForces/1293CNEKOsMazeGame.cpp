#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
bool maze[2][maxN + 2];
struct At
{
  int r1, r2, dir;
  bool operator<(const At &other) const
  {
    return r1 < other.r1 || (r1 == other.r1 && r2 < other.r2) || (r1 == other.r1 && r2 == other.r2 && dir < other.dir);
  }
};
set<At> blocked;

void update(int r, int c, bool toAdd)
{
  DEBUG printf("%d %d - %d\n", r, c, maze[r][c]);
  for (int j = -1; j <= 1; j ++)
    if (maze[1 - r][c + j])
    {
      At at = j < 0 ? At{c + j, c, 1 - r} : j == 0 ? At{c, c, -1} : At{c, c + j, r};
      if (toAdd)
        blocked.insert(at);
      else
        blocked.erase(at);
    }
}

int main()
{
  int t = 0;
  while (scanf("%d %d", &n, &q) != EOF)
  {
    if (t ++) printf("\n");

    blocked.clear();
    memset(maze, false, sizeof(maze));
    for (int i = 0; i < q; i ++)
    {
      int r, c; scanf("%d %d", &r, &c); r --;

      update(r, c, !maze[r][c]);
      
      printf("%s\n", blocked.empty() ? "Yes" : "No");
      maze[r][c] = !maze[r][c];
    }
  }
  return 0;
}