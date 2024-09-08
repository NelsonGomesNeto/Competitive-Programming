#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
int a[maxN];
bool visited[maxN];

void dfs(int i)
{
  if (visited[i]) return;
  visited[i] = true;
  dfs(a[i]);
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      --a[i];
    }

    fill(visited, visited+n, false);
    for (int i = 0; i < n; ++i)
      if (!visited[i])
        visited[a[i]] = true;

    vector<int> notVisited;
    for (int i = 0; i < n; ++i)
      if (!visited[i])
        notVisited.push_back(i);
    printf("%d\n", (int)notVisited.size());
    for (int i = 0; i < notVisited.size(); ++i)
      printf("%d%c", notVisited[i] + 1, i + 1 < notVisited.size() ? ' ' : '\n');
  }
  return 0;
}
