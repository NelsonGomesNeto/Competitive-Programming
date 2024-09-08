#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
vector<int> tree[2*maxN + 1];
int height[2*maxN + 1];

void dfs(int u = 0, int depth = 0)
{
  height[u] = depth;
  for (int v : tree[u])
    dfs(v, depth + 1);
}

int main()
{
  int hehe = 0;
  while (~scanf("%d", &n))
  {
    if (hehe++) printf("-------------\n");
    int nAns = 2*n + 1;
    for (int i = 0; i < nAns; ++i) tree[i].clear();

    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]); --a[i];
      tree[a[i]].push_back(2*(i + 1) - 1);
      tree[a[i]].push_back(2*(i + 1));
    }

    dfs();

    for (int i = 0; i < nAns; ++i)
      printf("%d\n", height[i]);
  }
  return 0;
}
