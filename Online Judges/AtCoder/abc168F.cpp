#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  compress the coordinates
  floodfill
*/

const int maxN = 1e3 + 10;
const int maxX = 6*maxN;
int n, m, limitx, limity;
lli horizontal[3][maxN], vertical[3][maxN];

vector<lli> xs, ys;
unordered_map<lli, int> compx, compy;
lli revx[maxX], revy[maxX];

int mat[maxX][maxX];

int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool bfs(int sx, int sy)
{
  queue<pair<int, int>> q;
  q.push({sx, sy});
  while (!q.empty())
  {
    int x = q.front().first, y = q.front().second; q.pop();
    if (x < 0 || x >= limitx || y < 0 || y >= limity) return true;
    if (mat[x][y] != 0) continue;
    mat[x][y] = 2;
    for (int k = 0; k < 4; k++)
    {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= limitx || ny < 0 || ny >= limity) return true;
      if (mat[nx][ny] == 0)
        q.push({x + dx[k], y + dy[k]});
    }
  }
  return false;
}

void compressCoordinates(vector<lli> &arr, unordered_map<lli, int> &comp, lli rev[])
{
  sort(arr.begin(), arr.end());
  arr.resize(distance(arr.begin(), unique(arr.begin(), arr.end())));

  comp.clear();
  for (int i = 0; i < arr.size(); i++) comp[arr[i]] = 2*i, rev[2*i] = arr[i];
}

int main()
{
  int t = 0;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    if (t++) memset(mat, 0, sizeof(mat));

    // Read lines
    xs.push_back(0), ys.push_back(0);
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < 3; j++)
        scanf("%lld", &horizontal[j][i]);
      xs.push_back(horizontal[0][i]), xs.push_back(horizontal[1][i]);
      ys.push_back(horizontal[2][i]);
    }

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < 3; j++)
        scanf("%lld", &vertical[j][i]);
      xs.push_back(vertical[0][i]);
      ys.push_back(vertical[1][i]), ys.push_back(vertical[2][i]);
    }

    // Compress coordinates (multiply by 2 so we can iterate through 0.5 positions)
    compressCoordinates(xs, compx, revx), compressCoordinates(ys, compy, revy);
    for (int i = 0; i < n; i++)
    {
      horizontal[0][i] = compx[horizontal[0][i]], horizontal[1][i] = compx[horizontal[1][i]];
      horizontal[2][i] = compy[horizontal[2][i]];
    }
    for (int i = 0; i < m; i++)
    {
      vertical[0][i] = compx[vertical[0][i]];
      vertical[1][i] = compy[vertical[1][i]], vertical[2][i] = compy[vertical[2][i]];
    }

    // max x and y positions
    limitx = 2*xs.size() + 1, limity = 2*ys.size() + 1;

    for (int i = 0; i < n; i++)
      for (int j = horizontal[0][i]; j <= horizontal[1][i]; j++)
        mat[j][horizontal[2][i]] = 1;
    for (int i = 0; i < m; i++)
      for (int j = vertical[1][i]; j <= vertical[2][i]; j++)
        mat[vertical[0][i]][j] = 1;

    // bfs from (0, 0); dfs would do, but it can easily go out of memory :^)
    int zerox = compx[0], zeroy = compy[0];
    bool beyond = bfs(zerox, zeroy);
    DEBUG
      for (int y = 0; y < limity; y++)
      {
        for (int x = 0; x < limitx; x++)
          if (x == zerox && y == zeroy) printf("x");
          else printf("%c", mat[x][y] == 1 ? '@' : mat[x][y] == 2 ? ((x & 1LL & y) ? '~' : '.') : ' ');
        printf("\n");
      }

    if (beyond) printf("INF\n");
    else
    {
      // add each reached block accordingly to it's size
      long long int ans = 0;
      for (int x = 1; x < limitx; x += 2)
      {
        lli xdiff = revx[x + 1] - revx[x - 1];
        for (int y = 1; y < limity; y += 2)
          if (mat[x][y] == 2)
            ans += xdiff * (revy[y + 1] - revy[y - 1]);
      }
      printf("%lld\n", ans);
    }
  }
  return 0;
}