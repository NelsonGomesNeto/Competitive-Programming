#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 11; int n, m;
struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  bool operator==(const Pos &other) const { return i == other.i && j == other.j; }
};
Pos origin, destination;

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
bool visited[maxN][maxN];
int dfs(Pos u = origin)
{
  if (u == destination) return 1;
  int ans = 0;
  for (int k = 0; k < 4; k++)
  {
    Pos newPos = {u.i + 2*di[k], u.j + 2*dj[k]};
    if (newPos.i < 0 || newPos.j < 0 || newPos.i >= n || newPos.j >= m || visited[newPos.i][newPos.j]) continue;
    for (int p = 0; p < 2; p++) visited[u.i + p*di[k]][u.j + p*dj[k]] = true;
    ans = max(ans, dfs(newPos) + 2);
    for (int p = 0; p < 2; p++) visited[u.i + p*di[k]][u.j + p*dj[k]] = false;
  }
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    origin.read();
    destination.read();

    int ans = dfs();
    printf("%d\n", ans);
  }
  return 0;
}