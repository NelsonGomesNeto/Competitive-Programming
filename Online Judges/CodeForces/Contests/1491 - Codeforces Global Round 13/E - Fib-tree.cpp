#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;


const int maxN = 2e5; int n;
int isFib[maxN + 1];
typedef struct Tree;
list<int> tree[maxN];bool can = true;
queue<Tree> tq;

void removeEdge(int u, int v)
{
  for (auto it = tree[u].begin(); it != tree[u].end(); it++)
    if (*it == v)
    {
      tree[u].erase(it);
      break;
    }
}

struct Tree
{
  int root, size;
  int aRoot, bRoot, splitSize;

  Tree() { }
  Tree(int root, int size) : root(root), size(size)
  {
  }
  bool splitTree()
  {
    aRoot = -1, bRoot = -1;
    calcSubtree(root, -1);
    
    if (bRoot != -1)
    {
      Tree a = Tree(aRoot, size - splitSize), b = Tree(bRoot, splitSize);

      removeEdge(aRoot, bRoot);
      removeEdge(bRoot, aRoot);

      tq.push(a); tq.push(b);
      return true;
    }
    return false;
  }
  int calcSubtree(int u, int prv)
  {
    int curr = 1;
    for (int v: tree[u])
      if (v != prv)
        curr += calcSubtree(v, u);

    if (isFib[curr] && isFib[size - curr])
      aRoot = prv, bRoot = u, splitSize = curr;
    return curr;
  }
};

int main()
{
  for (int a = 1, b = 1; a <= maxN;)
  {
    isFib[a] = true;
    int aux = b;
    b = a + b;
    a = aux;
  }

  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      tree[i].clear();

    Tree base = Tree(0, n);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    while (!tq.empty())
      tq.pop();
    tq.push(base);

    can = isFib[n];
    while (!tq.empty() && can)
    {
      Tree t = tq.front(); tq.pop();
      if (t.size <= 3)
        continue;

      if (!t.splitTree())
      {
        can = false;
        break;
      }
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
