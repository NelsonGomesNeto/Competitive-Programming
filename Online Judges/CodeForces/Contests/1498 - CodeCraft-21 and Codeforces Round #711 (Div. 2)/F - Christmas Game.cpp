#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Do you know Nim Game? https://en.wikipedia.org/wiki/Nim
  The game that this problem proposes is a Nim Game, but on a tree instead
  of an array.

  Let's first try to solve for k = 1:
    * Notice that nodes at even depths (0-indexing) are completely useless
      * Coins at root (depth = 0) aren't useful anymore, since we can't move with them
      * Every move on an even depths will move coins to odd depths. With that said, if
        we move a coin from (even -> odd), the other player will always be able to move
        a coin from (odd -> even). So even depths moves are always bad.
      * So, we only need to consider the coins at odd depths
    * ans[i] = oddXorSumForRoot(i) != 0

  We can generalize that for any k with useful(depth) = floor(depth / k) is odd.
  Now we just need to calculate the oddXorSumForEachRoot using this useful function.

  We can do that with Tree DP and rerooting:
  * Choose a root
  * memo[u][d][odd] = xorSum from u, where u has depth d and is "odd" (useful)
      u - current node
      d - current depth
      odd - useful(depth)
        Notice that using odd, we can keep depth < k
  * Rerooting can be done by starting with all possible "d" and "odd" from root
    and subtracting d instead of adding. So that if we reached a node with d = 0
    and odd = 0: we know that we chose the perfect start for "d" and "odd".
      You will also need to keep track of the current xorSum
      Use the full xorSum, and through the dfs: remove the incorrect parts and
      add the correct ones.
*/

const int maxN = 1e5, maxK = 20; int n, k;
vector<int> tree[maxN];
lli a[maxN];

int ans[maxN];

lli naive(int u, int d = 0, int odd = 0, int prv = -1)
{
  if (d == k)
    d = 0, odd = !odd;

  lli ans = odd ? a[u] : 0;
  for (int v: tree[u])
    if (v != prv)
      ans ^= naive(v, d + 1, odd, u);
  return ans;
}

lli memo[maxN][maxK][2];
lli dfs(int u = 0, int d = 0, bool odd = false, int prv = -1)
{
  if (d == -1)
    d = k - 1, odd = !odd;
  if (d == k)
    d = 0, odd = !odd;

  lli &ans = memo[u][d][odd];
  if (ans != -1)
    return ans;

  ans = odd ? a[u] : 0;
  for (int v: tree[u])
    if (v != prv)
      ans ^= dfs(v, d + 1, odd, u);

  return ans;
}

lli reRootedAns[maxN];
void dfs2(int u = 0, int d = 0, bool odd = false, lli totalXorSum = 0, int prv = -1)
{  
  if (d == -1)
    d = k - 1, odd = !odd;

  if (d == 0 && odd == false)
    reRootedAns[u] = totalXorSum;

  for (int v: tree[u])
    if (v != prv)
    {
      lli newTotalXorSum = totalXorSum;
      newTotalXorSum ^= dfs(v, d + 1, odd, u); // remove
      newTotalXorSum ^= dfs(v, d - 1, odd, u); // add

      dfs2(v, d - 1, odd, newTotalXorSum, u);
    }
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; i++)
      tree[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    memset(reRootedAns, -1, sizeof(reRootedAns));
    for (int d = 0; d < k; d++)
      for (int odd = 0; odd < 2; odd++)
        dfs(0, d, odd);
    for (int d = 0; d < k; d++)
      for (int odd = 0; odd < 2; odd++)
        dfs2(0, d, odd, dfs(0, d, odd));
    ans[0] = memo[0][0][false] != 0;

    for (int i = 1; i < n; i++)
    {
      assert(reRootedAns[i] != -1);
      lli xorSum = reRootedAns[i];
      ans[i] = xorSum != 0;
    }
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
