#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3;
int n, m;
char ss[maxN + 1];
string maze[maxN];
int visited[maxN][maxN];

bool is_person(char c) {
  return c == '>' || c == '<' || c == '^' || c == 'v';
}
pair<int, int> pdir[256];

int di[4] = {0, 1, -1, 0};
int dj[4] = {1, 0, 0, -1};
int bfs() {
  int si, sj, ei, ej;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (maze[i][j] == 'S')
        si = i, sj = j;
      else if (maze[i][j] == 'G')
        ei = i, ej = j;
  memset(visited, false, sizeof(visited));

  queue<tuple<int, int, int>> q;
  q.emplace(si, sj, 0);
  while (!q.empty()) {
    auto [i, j, c] = q.front();
    q.pop();
    if (visited[i][j]) continue;
    visited[i][j] = true;

    if (i == ei && j == ej) return c;

    for (int d = 0; d < 4; ++d) {
      int ni = i + di[d], nj = j + dj[d];
      if (ni >= 0 && nj >= 0 && ni < n && nj < m && (maze[ni][nj] == '.' || maze[ni][nj] == 'S' || maze[ni][nj] == 'G'))
        q.emplace(ni, nj, c + 1);
    }
  }
  return -1;
}

int main()
{
  pdir['>'] = make_pair(0, 1);
  pdir['^'] = make_pair(-1, 0);
  pdir['v'] = make_pair(1, 0);
  pdir['<'] = make_pair(0, -1);

  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < n; ++i) {
      scanf(" %s", ss);
      maze[i] = string(ss);
    }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) {
        if (is_person(maze[i][j])) {
          int ni = i + pdir[maze[i][j]].first, nj = j + pdir[maze[i][j]].second;
          while (ni >= 0 && nj >= 0 && ni < n && nj < m && (maze[ni][nj] == '.' || maze[ni][nj] == '!')) {
            maze[ni][nj] = '!';
            ni += pdir[maze[i][j]].first, nj += pdir[maze[i][j]].second;
          }
        }
      }

    DEBUG {
      for (int i = 0; i < n; ++i) {
        printf("%s\n", maze[i].c_str());
      }
    }

    int ans = bfs();
    printf("%d\n", ans);
  }
  return 0;
}
