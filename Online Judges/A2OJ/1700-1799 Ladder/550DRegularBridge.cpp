#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxK = 100; int n, k;
vector<pair<int, int>> edges;

int main()
{
  while (scanf("%d", &k) != EOF)
  {
    if (k == 1) printf("YES\n2 1\n1 2\n");
    else if (!(k & 1)) printf("NO\n");
    else
    {
      n = 2*k + 4;
      for (int i = 2; i <= k; i ++) edges.push_back({1, i});
      for (int i = 2; i <= k; i ++)
      {
        for (int j = i + 1 + !(i & 1); j <= k; j ++)
          edges.push_back({i, j});
        edges.push_back({i, k + 1}), edges.push_back({i, k + 2});
      }
      edges.push_back({k + 1, k + 2});
      for (int i = 0, end = edges.size(); i < end; i ++)
        edges.push_back({edges[i].first + k + 2, edges[i].second + k + 2});
      edges.push_back({1, k + 3});

      printf("YES\n%d %d\n", n, (int) edges.size());
      for (auto e: edges) printf("%d %d\n", e.first, e.second);
    }
  }
  return 0;
}
