#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  Since b_i = min(a_i, a_(i+1)) and c_i = max(a_i, a_(i+1))
  Then in the array, you will either have:
    [..., a_i, a_(i+1), ...]
    [..., a_(i+1), a_i, ...]
    But they will always be side by side
  Since this will be true for every i, and any permutation will work:
  we just have to find the optimal trail of numbers that will keep up
  with the restrictions. Exactly, Eulerian Trail (Path)
  If (b[i] > c[i] for any i) or (there's no Eulerian Path), answer will be -1

  So, for every i:
    addEdge(b[i], c[i])
  print(eulerianPath)
*/

const int maxN = 1e5; int n;
int b[maxN - 1], c[maxN - 1];
void read(int array[])
{
  for (int i = 0; i < n - 1; i ++) scanf("%d", &array[i]);
}

struct Edge { int to, back; bool visited; };
map<int, int> numberMap; int revNumberMap[2*maxN];
vector<Edge> graph[2*maxN];
vector<int> path;
int ptr[2*maxN];
void eulerianPath(int u)
{
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    auto &v = graph[u][p];
    if (!v.visited)
    {
      v.visited = true, graph[v.to][v.back].visited = true;
      eulerianPath(v.to);
    }
  }
  path.push_back(revNumberMap[u]);
}

void addToMap(int bb, int cc)
{
  if (!numberMap.count(bb))
  {
    revNumberMap[numberMap.size()] = bb;
    numberMap[bb] = numberMap.size();
  }
  if (!numberMap.count(cc))
  {
    revNumberMap[numberMap.size()] = cc;
    numberMap[cc] = numberMap.size();
  }
  int u = numberMap[bb], v = numberMap[cc];
  graph[u].push_back({v, (int) graph[v].size() + (u == v), false});
  graph[v].push_back({u, (int) graph[u].size() - 1, false});
}

int main()
{
  scanf("%d", &n);
  read(b); read(c);

  bool can = true;
  for (int i = 0; i < n - 1; i ++)
  {
    if (b[i] > c[i]) can = false;
    addToMap(b[i], c[i]);
  }
  int odd = 0, first = 0;
  for (int i = 0; i < 2*n; i ++)
    if (graph[i].size() & 1)
      odd ++, first = i;
  if (can) can = odd == 0 || odd == 2;

  if (!can) printf("-1\n");
  else
  {
    eulerianPath(first);
    if (path.size() != n) printf("-1\n"); // Handles when the graph isn't connected
    else
    {
      for (int i: path) printf("%d ", i);
      printf("\n");
    }
  }

  return(0);
}