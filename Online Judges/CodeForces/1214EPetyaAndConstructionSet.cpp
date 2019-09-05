#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
vector<pair<int, int>> edges;
int d[maxN];
struct Node
{
  int u, d;
  bool operator<(const Node &other) const
  {
    return d > other.d;
  }
};
vector<Node> bamboo;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    bamboo.clear(), edges.clear();
  
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &d[i]);
      bamboo.push_back({2*i, d[i]});
    }
    sort(bamboo.begin(), bamboo.end());

    for (int i = 0; i < n - 1; i ++)
      edges.push_back({bamboo[i].u, bamboo[i + 1].u});

    for (int i = 0; i < n; i ++)
      if (i >= bamboo[i].d) edges.push_back({bamboo[i].u + 1, bamboo[i - (bamboo[i].d - 1)].u});
      else
      {
        int j = i + (bamboo[i].d - 1);
        edges.push_back({bamboo[j].u, bamboo[i].u + 1});
        if (j == bamboo.size() - 1) bamboo.push_back({bamboo[i].u + 1, 0});
      }

    for (auto &e: edges)
      printf("%d %d\n", e.first + 1, e.second + 1);
  }
  return(0);
}
