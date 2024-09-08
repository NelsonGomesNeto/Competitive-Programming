#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  Well, I don't need to check every single path
  I just need to check if the path from a root to a leaf
  has any repeated value
  If it does: the root isn't distinctive

  I can choose any root
  Then, for each leaf: I build a multiset of the path from
  root to the leaf.

  With that, I can compare a leaf with every other leaf
  If they have intersection: every node in both paths can't
  be a distinctive root.



*/

set<int> dfs(int u = 0, int prv = -1)
{
  // for (int v: tree[u])
  // {

  // }
}

int main()
{
  
  return 0;
}
