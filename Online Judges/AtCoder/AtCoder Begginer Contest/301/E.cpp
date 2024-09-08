#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 300, maxCandies = 18, inf = 1e7;
char mat[maxN][maxN + 1];
int candiesMask[maxN][maxN];
int n, m, t;

int di[4] = {0, 1, -1, 0};
int dj[4] = {1, 0, 0, -1};

struct Pos;
vector<Pos> graph[maxN][maxN];
struct Pos
{
  int i, j;
  bool operator==(const Pos& other) const { return i == other.i && j == other.j; }
  vector<Pos> directions()
  {
    return graph[i][j];
  }
  bool hasCandy()
  {
    return mat[i][j] == 'o';
  }
  int candyMask()
  {
    return candiesMask[i][j];
  }
};
Pos start, goal;
int distToGoal(const Pos& p)
{
  return abs(p.i - goal.i) + abs(p.j - goal.j);
}

vector<Pos> getDirections(int i, int j)
{
  vector<Pos> res;
  for (int d = 0; d < 4; ++d)
  {
    int ni = i + di[d], nj = j + dj[d];
    if (ni < 0 || nj < 0 || ni >= n || nj >= m || mat[ni][nj] == '#')
      continue;
    res.push_back(Pos{ni, nj});
  }
  return res;
}

int shortestPath[maxN][maxN];
void fillShortestPath()
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      shortestPath[i][j] = inf;
  queue<pair<Pos, int>> q;
  q.push({goal, 0});
  while (!q.empty())
  {
    auto [p, d] = q.front();
    q.pop();

    if (shortestPath[p.i][p.j] != inf) continue;
    shortestPath[p.i][p.j] = d;

    for (Pos np : p.directions())
      q.push({np, d + 1});
  }
}

struct State
{
  Pos pos; int steps, candies, candiesMask;
  bool operator<(const State& other) const
  {
    // Consider adding distance to goal heuristic.
    // return steps > other.steps || (steps == other.steps && candies < other.candies);
    return candies < other.candies
        || (candies == other.candies && steps > other.steps);
  }
};
int memo[maxN][maxN][maxCandies];
int dijkstra()
{
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      fill(memo[i][j], memo[i][j]+maxCandies, inf);
  priority_queue<State> pq;
  pq.push(State{start, 0, 0, 0});
  memo[start.i][start.j][0] = 0;

  int ans = -1;
  while (!pq.empty())
  {
    State now = pq.top();
    pq.pop();

    if (now.steps > t)
      continue;
    if (now.steps > memo[now.pos.i][now.pos.j][now.candies])
      continue;

    DEBUG printf("\t%d %d | %d %d %d | %d\n", now.pos.i, now.pos.j, now.steps, shortestPath[now.pos.i][now.pos.j], t - (now.steps + shortestPath[now.pos.i][now.pos.j]), now.candies);
    if (now.pos == goal)
      ans = max(ans, now.candies);

    for (Pos p : now.pos.directions())
    {
      if ((now.candiesMask & p.candyMask()) != 0) continue;

      int newCandies = now.candies + p.hasCandy();
      int newSteps = now.steps + 1;
      if (newSteps < memo[p.i][p.j][newCandies])
        pq.push(State{p, memo[p.i][p.j][newCandies] = newSteps, newCandies, now.candiesMask | p.candyMask()});
    }
  }

  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &t))
  {
    memset(candiesMask, 0, sizeof(candiesMask));
    for (int i = 0; i < n; ++i)
      scanf(" %s", mat[i]);
    int candyCount = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
      {
        if (mat[i][j] == 'S')
          start = Pos{i, j};
        if (mat[i][j] == 'G')
          goal = Pos{i, j};
        if (mat[i][j] == 'o')
        {
          candiesMask[i][j] = 1LL << candyCount;
          ++candyCount;
        }

        graph[i][j] = getDirections(i, j);
      }

    // fillShortestPath();
    int ans = dijkstra();
    printf("%d\n", ans);
    DEBUG return 0;
  }
  return 0;
}
