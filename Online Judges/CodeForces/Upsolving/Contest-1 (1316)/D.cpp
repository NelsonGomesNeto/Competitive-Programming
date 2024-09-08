#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
struct Pos
{
  int i, j;
  bool operator!=(Pos &other) const { return i != other.i && j != other.j; }
};
Pos dest[maxN][maxN];

char ans[maxN][maxN + 1];
vector<Pos> xs;

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
char dir[4] = {'L', 'R', 'U', 'D'};
int opposite[4] = {1, 0, 3, 2};

bool dfs(int i, int j, int prvK)
{
  DEBUG printf("\t%d %d %c\n", i, j, prvK == -1 ? '.' : dir[prvK]);
  if (i < 0 || j < 0 || i >= n || j >= n) return false;
  if (ans[i][j] != '.') return ans[i][j] != 'X' && ans[i][j] != '-';

  for (int k = 0; k < 4; k ++)
    if (prvK != k)
    {
      ans[i][j] = dir[opposite[k]];
      if (!dfs(i + di[k], j + dj[k], opposite[k]))
        ans[i][j] = '.';
      else
        break;
    }
  if (ans[i][j] == '.')
  {
    ans[i][j] = '-';
    return false;
  }
  return true;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    xs.clear();
    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < n; j ++)
      {
        ans[i][j] = '.';
        scanf("%d %d", &dest[i][j].i, &dest[i][j].j);
        dest[i][j].i --, dest[i][j].j --;
        if (i == dest[i][j].i && j == dest[i][j].j)
          ans[i][j] = 'X', xs.push_back({i, j});
      }
      ans[i][n] = '\0';
    }

    bool valid = true;
    for (Pos &x: xs)
    {
      queue<pair<Pos, char>> q;
      for (int k = 0; k < 4; k ++)
        q.push({{x.i + di[k], x.j + dj[k]}, dir[k]});
      while (!q.empty())
      {
        Pos u = q.front().first; char direction = q.front().second;
        q.pop();
        if (ans[u.i][u.j] != '.' || dest[u.i][u.j] != x) continue;
        ans[u.i][u.j] = direction;
        for (int k = 0; k < 4; k ++)
          q.push({{u.i + di[k], u.j + dj[k]}, dir[k]});
      }
    }
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (ans[i][j] == '.' && !dfs(i, j, -1))
          valid = false;

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (ans[i][j] == '.' || ans[i][j] == '-')
          valid = false;

    if (valid)
    {
      printf("VALID\n");
      for (int i = 0; i < n; i ++)
        printf("%s\n", ans[i]);
    }
    else
      printf("INVALID\n");
  }
  return 0;
}
