#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;
vector<int> tree[maxN];
vector<pair<int, int>> tree2[maxN];

/*
I will either query the value of u or not
  if we know u:
    we must uncover childs[u].size() - 1
  if we don't know u:
    we must uncover childs[u].size()
*/
lli memo[maxN][2];
lli dfs(int u, bool queryU, bool root = false)
{
  lli &ans = memo[u][queryU];
  if (ans != -1) return ans;

  if (tree[u].empty())
    return ans = 1;

  ans = 0;
  vector<lli> prefix(tree[u].size() + 1), suffix(tree[u].size() + 1), all(tree[u].size());

  prefix[0] = suffix[tree[u].size()] = 1;
  for (int i = 0; i < tree[u].size(); i++)
    all[i] = dfs(tree[u][i], true);
  for (int i = 0; i < tree[u].size(); i++)
    prefix[i + 1] = prefix[i] * all[i] % mod;
  for (int i = tree[u].size() - 1; i >= 0; i--)
    suffix[i] = suffix[i + 1] * all[i] % mod;

  for (int i = 0; i < tree[u].size(); i++)
  {
    lli now = prefix[i] * suffix[i + 1] % mod * dfs(tree[u][i], false) % mod;
    DEBUG printf("\tu: %d, dont query: %d - %lld\n", u + 1, tree[u][i] + 1, now);
    ans = (ans + now) % mod;
  }

  if (queryU && !root)
    ans = (ans + prefix[tree[u].size()]) % mod;

  DEBUG printf("%d, queryU: %d, root: %d - %lld\n", u + 1, queryU, root, ans);

  return ans;
}

void printTree(int u = 0, int depth = 0)
{
  if (depth < 3)
  {
    for (int i = 0; i < depth; i++)
      printf("   ");
    printf("%3d\n", u + 1);
  }
  for (int v: tree[u])
    printTree(v, depth + 1);
}

int main()
{
  scanf("%d", &n);
  for (int i = 1; i < n; i++)
  {
    int p; scanf("%d", &p); p--;
    tree[p].push_back(i);
  }
  DEBUG printTree();

  memset(memo, -1, sizeof(memo));
  lli mult = 1;
  int u = 0;
  bool isLine = false;
  while (tree[u].size() == 1)
    u = tree[u][0], mult++;
  if (tree[u].size() == 0)
    isLine = true;
  DEBUG printf("root: %d || %lld\n", u + 1, mult);

  lli ans = mult;
  if (!isLine)
  {
    ans = mult * dfs(u, true, true) % mod;
    DEBUG printf("query root: %lld\n", ans);

    lli res = 1;
    for (int v: tree[u])
    {
      lli now = dfs(v, true);
      DEBUG printf("\tdont query root (%d): %lld\n", v + 1, now);
      res = res * now % mod;
    }
    DEBUG printf("dont query root: %lld\n", res);
    ans = (ans + res) % mod;
  }

  printf("%lld\n", ans);

  return 0;
}