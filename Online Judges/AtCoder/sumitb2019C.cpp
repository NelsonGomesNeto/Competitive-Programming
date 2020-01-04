#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e5 + 1;
int x;
bool visited[maxX];
void bfs()
{
  queue<int> q; q.push(0);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (u >= maxX || visited[u]) continue;
    visited[u] = true;
    for (int i = 100; i <= 105; i ++)
      q.push(u + i);
  }
}

int main()
{
  memset(visited, false, sizeof(visited));
  bfs();

  while (scanf("%d", &x) != EOF)
    printf("%d\n", visited[x]);
  return 0;
}