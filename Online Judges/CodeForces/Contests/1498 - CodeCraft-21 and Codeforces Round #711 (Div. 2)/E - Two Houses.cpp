#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int query(int a, int b)
{
  printf("? %d %d\n", a + 1, b + 1); fflush(stdout);
  char res[5]; scanf(" %s", res);
  return !strcmp(res, "Yes");
}

/*
  There is exactly one directed road between every pair of houses.

  So there's exaclty n*(n - 1) edges
  We just don't know the direction of them

  This implies that outgoing_edges_from[i] == (n - 1) - in[i]

  If a can't reach b:
    edge a -> b doesn't exist
    But edge a <- b does
    So, b can reach a
*/

const int maxN = 500;
int edges[maxN][maxN];
vector<int> graph[maxN];

int main()
{
  memset(edges, -1, sizeof(edges));

  int n; scanf("%d", &n);
  int in[n], out[n];
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &in[i]);
    out[i] = (n - 1) - in[i];
    graph[i].clear();
  }

  vector<pair<pair<int, int>, pair<int, int>>> kij;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (i != j && in[i] >= in[j])
        kij.push_back(make_pair(abs(in[i] - in[j]), make_pair(i, j)));
  sort(kij.begin(), kij.end());

  int a = -1, b = -1;
  for (auto &p: kij)
  {
    int v = p.first, aa = p.second.first, bb = p.second.second;
    // queries if aa -> bb (aa reaches bb)
    int res = query(aa, bb);
    if (res)
    {
      a = aa, b = bb;
      break;
    }
    else
    {
      edges[aa][bb] = 0;
      edges[bb][aa] = 1, graph[bb].push_back(aa);
    }
  }
  printf("! %d %d\n", a + 1, b + 1); fflush(stdout);

  return 0;
}
