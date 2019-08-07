#include <bits/stdc++.h>
using namespace std;

int topSortDfs(vector<int> graph[], int u, int color[], deque<int>& ans)
{
  if (color[u] != 0) return(!(color[u] - 1));
  color[u] = 1;
  for (auto v: graph[u])
    if (topSortDfs(graph, v, color, ans))
      return(1);

  color[u] = 2;
  ans.push_front(u);
  return(0);
}

int topSort(vector<int> graph[], int size, deque<int>& ans)
{
  int color[size]; memset(color, 0, sizeof(color));
  for (int i = 0; i <= size; i ++)
    if (color[i] == 0 && graph[i].size() && topSortDfs(graph, i, color, ans))
      return(1);

  return(0);
}

int main()
{
  int n, qChar = 25; scanf("%d", &n);
  vector<int> graph[qChar + 1];
  char name[n][100 + 1];
  for (int i = 0; i < n; i ++) scanf("\n%s", name[i]);
  //for (int i = 'a'; i < 'z'; i ++)
    //graph[i - 'a'].push_back(i - 'a' + 1);

  int lolBug = 0;
  for (int i = 0, j = 0; i < n - 1; i ++, j = 0)
  {
    while (name[i][j] && name[i + 1][j] && name[i][j] == name[i + 1][j]) j ++;
    if (name[i][j] && name[i + 1][j])
      graph[name[i][j] - 'a'].push_back(name[i + 1][j] - 'a');
    if (name[i][j] && !name[i + 1][j])
      lolBug = 1;
  }

  deque<int> ans;
  if (topSort(graph, qChar, ans) || lolBug)
    printf("Impossible");
  else
  {
    int haveChanged[qChar + 1]; memset(haveChanged, 0, sizeof(haveChanged));
    for (auto i: ans) haveChanged[i] = 1;
    for (int i = 0; i <= qChar; i ++)
      if (!haveChanged[i])
        printf("%c", i + 'a');
    for (auto i: ans)
      printf("%c", i + 'a');
  }
  printf("\n");

  return(0);
}