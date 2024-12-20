#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1;
int n;
int fat[11];

bool visited[maxN];
int bfs()
{
  memset(visited, false, sizeof(visited));

  queue<pair<int, int>> q; q.push({0, 0});
  while (!q.empty())
  {
    int u = q.front().first, c = q.front().second; q.pop();
    if (u > n) continue;
    if (u == n) return c;

    if (visited[u]) continue;
    visited[u] = true;

    for (int i = 1; i <= 10; i++) 
      q.push({u + fat[i], c + 1});
  }
  return -1;
}

int fatRec(int n)
{
  if (n <= 1) return 1;
  return n * fatRec(n - 1);
}

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= 10; i++)
    fat[i] = i*fat[i - 1];

  while (scanf("%d", &n) != EOF)
  {
    int ans = bfs();

    // fat(n) = n * (n - 1) * (n - 2) * ... * 1
    // fat(n) é múltiplo de fat(n - 1)
    // fat(n) / fat(n - 1) = n é inteiro
    // int ans = 0;
    // for (int i = 10; n;)
    // {
    //   if (fat[i] > n) i--;
    //   else n -= fat[i], ans++;
    // }

    printf("%d\n", ans);
  }

  return 0;
}