#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Before solving for all roots, let's fix the root at 0 (any root will do)

  Notations:
    s[u] == u's subtree size (rooted at 0)
    divisions[u] = s[u] * (s[v] for every v in u's subtree)
    parent[u] = u's parent

  Ignoring the rules: ans = n! (all permutations)
  Adding the rules:
    (value of u < value of u's child) for every u
    u has s[u] values available, but only the smallest can be assigned to u
    The probability this event is (1 / s[u]):
      1 * (s[u] - 1)! out of s[u]! == (1 * (s[u] - 1)!) / (s[u]!) == 1 / s[u]
  So, ans = n! / (s[0] * s[1] * ... * s[n - 1])
    Since all rules must be applied

  To solve for all roots, we will need to apply re-rooting (try before reading below)
  Notice that for every node: divisions[u] will not change, since we're only
  considering nodes below u and they would continue below if u were the root.
  But we need to calculate aboveDivisions (divisions[parent[u]])

  dfs to calculate "s" and "divisions"
  Another dfs to calculate ans
    ans = n!
    ans /= aboveDivisions
    ans /= divisions[u]
    ans *= s[u]
      remove s[u] from divisions[u], since u's subtree size is now equal to n
    ans /= n
      add new s[u] size (which is n)

    for v in tree[u]:
      newAboveDivisions = divisions[u]
      newAboveDivisions /= divisions[v]
        Remove v's branch divisions
      newAboveDivisions /= s[u]
        Remove u's old subtree size
      newAboveDivisions *= (n - s[v])
        Add u's new subtree size
      newAboveDivisions *= aboveDivisions
        Add u's parent divisions

      dfs(v, newAboveDivisions)

*/

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
lli fat[maxN + 1], invFat[maxN + 1];

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli invMod(lli x)
{
  return modPow(x, mod - 2);
}

vector<int> tree[maxN];

// calculates subtreeSize and divisions rooted at 0
lli divisions[maxN];
int subtreeSize[maxN];
void dfs1(int u = 0, int prv = -1)
{
  divisions[u] = 1, subtreeSize[u] = 1;
  for (int v: tree[u])
    if (v != prv)
    {
      dfs1(v, u);
      subtreeSize[u] += subtreeSize[v];
      divisions[u] = divisions[u] * divisions[v] % mod;
    }
  divisions[u] = divisions[u] * subtreeSize[u] % mod;
}

// find and for each u through rerooting
lli ans[maxN];
void dfs2(int u = 0, int prv = -1, lli aboveDivisions = 1)
{
  ans[u] = fat[n];
  if (prv != -1) ans[u] = ans[u] * invMod(aboveDivisions) % mod;
  ans[u] = ans[u] * invMod(divisions[u]) % mod // apply u's childs divisions
                  * subtreeSize[u] % mod // remove previous u's subtree size
                  * invMod(n) % mod; // add new u's subtree size

  for (int v: tree[u])
    if (v != prv)
    {
      lli newAboveDivisions =
        divisions[u] * aboveDivisions % mod // add above's divisions
                     * invMod(divisions[v]) % mod // remove this branch's divisions
                     * invMod(subtreeSize[u]) % mod // remove previous u's subtree size
                     * (n - subtreeSize[v]) % mod; // add new u's subtree size
      dfs2(v, u, newAboveDivisions);
    }
}

int main()
{
  fat[0] = 1, invFat[0] = invMod(1);
  for (lli i = 1; i <= maxN; i++)
  {
    fat[i] = i * fat[i - 1] % mod;
    invFat[i] = invMod(fat[i]);
  }

  int t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t++) printf("-----------\n");
    for (int i = 0; i < n; i++) tree[i].clear();

    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    dfs1();
    dfs2();

    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}