#include <bits/stdc++.h>
using namespace std;
int s, d, r = 1;
int connections[10][10] = {{7, 8, 9, -1}, {2, 4, 5, -1}, {1, 3, 4, 5, 6, -1}, {2, 5, 6, -1}, {1, 2, 5, 7, 8, -1}, {1, 2, 3, 4, 6, 7, 8, 9, -1}, {2, 3, 5, 8, 9, -1}, {0, 4, 5, 8, -1}, {0, 4, 5, 6, 7, 9, -1}, {0, 5, 6, 8, -1}};
int visited[10];

int getNumber(string number)
{
  int now = 0, pot = 1;
  for (auto s: number)
  {
    now = now * pot + s - '0';
    pot *= 10;
  }
  return(now);
}

void bruteForce(vector<int> graph[], int u, int sum, int depth, string now, deque<string>& ans)
{
  // printf("%d %d %d %s %d\n", u, sum, depth, now.c_str(), getNumber(now));
  if (visited[u]) return;
  if (sum == s)
  {
    int first = 0;
    for (auto i: ans)
    {
      if (first) printf(" ");
      printf("%s", i.c_str());
      first = 1;
    } printf("\n");
  }
  if (depth == d && getNumber(now) + sum <= s)
  {
    string aux = now;
    aux.push_back('\0');
    ans.push_back(aux);
    bruteForce(graph, u, sum + getNumber(now), 0, "", ans);
    ans.pop_back();
  }
  visited[u] = 1;
  for (auto v: graph[u])
  {
    // printf("FREAKING SHIT %d %d %d\n", u, v, depth);
    if (depth < d)
    {
      string aux = now;
      aux.push_back(v + '0');
      bruteForce(graph, v, sum, depth + 1, aux, ans);
    }
    else if (v + sum + getNumber(now) == s)
    {
      string aux = now;
      aux.push_back('\0');
      ans.push_back(aux);
      aux = "";
      aux.push_back(v + '0');
      aux.push_back('\0');
      ans.push_back(aux);
      bruteForce(graph, u, v + sum + getNumber(now), 0, "", ans);
      ans.pop_back();
      ans.pop_back();
    }
  }
  visited[u] = 0;
}

int main()
{
  while (scanf("%d %d", &s, &d) && !(s == -1 && d == -1))
  {
    vector<int> graph[10];
    for (int i = 0, j = 0; i < 10; i ++, j = 0)
      while (connections[i][j] != -1)
      {
        graph[i].push_back(connections[i][j]);
        j ++;
      }

    printf("#%d\n", r ++);
    for (int i = 0; i < 10; i ++)
    {
      memset(visited, 0, sizeof(visited));
      deque<string> ans;
      string lol = "";
      lol.push_back(i + '0');
      bruteForce(graph, i, i, 1, lol, ans);
    }
  }
  return(0);
}
