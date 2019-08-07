#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
Notice that we can split the Stick Man in 3 levels:
(0) head, (1) body (and arms), (2) bottom (and legs).
Also notice that you can start a Stick Man from the
arm of another one, since only edges will be painted.

memo[u][level] will store the maximum amount of Stick Men we can
paint from node u and being at that level. We can fill it with a DFS.

DFS:
  jump: dfs(v, 0) means you will jump this edge
  paint: dfs(v, 1) + 1 means you will paint this edge (starting a new Stick Man) 

  head case: for every v in tree[u]: ans += max(jump, paint)
    since you are at head: you can always jump or paint
  body and bottom cases:
    for every v in tree[u]: mid.add({jump, paint})
    sort(mid) by paint - jump (asceding)
    ans += mid[0].jump + mid[1].jump
    for every m in mid[2:]:
      ans += max(m.jump, m.paint)
    notice that mid[0] and mid[1] are the arms/legs, so they can only choose
    to jump, the other nodes can choose to jump or paint, unless we are at
    body level; if so, we must find a node to be the bottom
    if body:
      best = -1 (since we can also choose not have a bottom and dismiss the stick we've started)
      for every m in mid[2:]:
        best = max(best, dfs(v, 2) - max(m.jump, m.paint))
      ans += best
*/

struct node
{
  int v, jump, paint;
  bool operator<(const node &a) const { return((paint - jump) < (a.paint - a.jump)); }
};

const int maxN = 1e5, inf = 1e8;
vector<int> tree[maxN];
int memo[maxN][3];
int dfs(int u, int level)
{
  if (memo[u][level] == -1)
  {
    int ans = 0;
    if (level == 0)
    {
      for (int &v: tree[u]) ans += max(dfs(v, 0), dfs(v, 1) + 1);
    }
    else
    {
      if (tree[u].size() < 2) return(memo[u][level] = -inf);
      vector<node> mid;
      for (int i = 0; i < tree[u].size(); i ++)
        mid.push_back({tree[u][i], dfs(tree[u][i], 0), dfs(tree[u][i], 1) + 1});
      sort(mid.begin(), mid.end());

      ans += mid[0].jump + mid[1].jump;
      for (int i = 2; i < mid.size(); i ++)
        ans += max(mid[i].jump, mid[i].paint);
      
      if (level == 1)
      {
        int best = -1;
        for (int i = 2; i < mid.size(); i ++)
          best = max(best, dfs(mid[i].v, 2) - max(mid[i].jump, mid[i].paint));
        ans += best;
      }
    }
    memo[u][level] = ans;
  }
  return(memo[u][level]);
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 1, j; i < n; i ++)
  {
    scanf("%d", &j); j --;
    tree[j].push_back(i);
  }
  memset(memo, -1, sizeof(memo));
  int ans = dfs(0, 0);
  printf("%d\n", ans);
  return(0);
}