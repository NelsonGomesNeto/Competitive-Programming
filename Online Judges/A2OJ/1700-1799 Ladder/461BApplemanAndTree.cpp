#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  We must be able to count:
    memo[u][0] = the number of ways u's subtree has 0 black vertices
    memo[u][1] = the number of ways u's subtree has 1 black vertice
      Which is the answer we want

  There are 4 cases to be considered:
    if (u is black and we want to count memo[u][0])
      memo[u][0] = 0
      (Since u is black, there's no way we can make a subtree
      with 0 black vertices)
    if (u is white and we want to count memo[u][1])
      ans0 (with 0 black vertices) = 1
      ans1 (with 1 black vertices) = 0
      for v in u.childs:
        ans1 = ans0 * memo[v][1] + ans1 * (memo[v][0] + memo[v][1])
          ans0 * memo[v][1] is:
            the number of ways u's subtree has 0 black vertices (with all childs before v)
            multiplied by the number of ways v is a subtree with 1 black vertices. So
            we're connecting them.
          ans1 * (memo[v][0] + memo[v][1]) == ans1 * memo[v][0] + ans1 * memo[v][1] is:
            the number of ways u's subtree has 1 black vertices (with all childs before v)
            multiplied by either connecting v to u's subtree (memo[v][0]) or not (memo[v][1]).
        ans0 = ans0 * (memo[v][0] + memo[v][1])
          Same observation above, just that memo[v][1] is connecting v to u's subtree as well
      memo[u][1] = ans1
    if (u is black and we want to count memo[u][1]
      or u is white and we want to count memo[u][0])
      memo[u][u is black] = 1
      for v in u.childs:
        memo[u][u is black] *= memo[v][0] + memo[v][1]
          u is black:
            memo[v][0], v will have to be connected with u
            memo[v][1], v will have to be disconnected with u
          u isn't black:
            memo[v][0], v will have to be connected with u
            memo[v][1], v will have to be connected with u
          either way, we have to consider memo[v][0] and memo[v][1]
*/

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;
vector<int> tree[maxN];
int black[maxN];

lli memo[maxN][2];
void dfs(int u = 0, int b = 1)
{
  if (memo[u][b] == -1)
  {
    for (int v: tree[u])
      dfs(v, 0), dfs(v, 1);

    if (black[u] && !b)
      memo[u][b] = 0;
    else if (!black[u] && b)
    {
      lli ans0 = 1, ans1 = 0;
      for (int v: tree[u])
      {
        ans1 = ans1 * ((memo[v][0] + memo[v][1]) % mod) % mod;
        ans1 = (ans1 + ans0 * memo[v][1] % mod) % mod;
        ans0 = ans0 * ((memo[v][0] + memo[v][1]) % mod) % mod;
      }
      memo[u][b] = ans1;
    }
    else
    {
      memo[u][b] = 1;
      for (int v: tree[u])
        memo[u][b] = memo[u][b] * ((memo[v][0] + memo[v][1]) % mod) % mod;
    }
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 1; i < n; i ++)
  {
    int p; scanf("%d", &p);
    tree[p].push_back(i);
  }
  for (int i = 0; i < n; i ++)
    scanf("%d", &black[i]);

  memset(memo, -1, sizeof(memo));
  dfs();
  printf("%lld\n", memo[0][1]);

  return 0;
}