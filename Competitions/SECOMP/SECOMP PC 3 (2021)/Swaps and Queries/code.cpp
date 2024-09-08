#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int blockSize = 500;
const int maxN = 1e5; int n, q;
int a[maxN];
struct Block
{
  int lo, hi;
  set<int> values, nvalues;
  void insert(int x) { values.insert(x), nvalues.insert(-x); }
  void erase(int x) { values.erase(x), nvalues.erase(-x); }
};
vector<Block> blocks;
int posToBlock[maxN];

void updateAns(int &ans, int op, int v, int x)
{
  if (op == 2)
  {
    if (v >= x) ans = min(ans, v);
  }
  else
  {
    if (v <= x) ans = max(ans, v);
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    blocks.clear();
    for (int i = 0; i < n; i += blockSize + 1)
    {
      Block b = Block{i, min(i + blockSize, n - 1), {}, {}};
      for (int j = b.lo; j <= b.hi; j++)
      {
        posToBlock[j] = blocks.size();
        b.insert(a[j]);
      }
      blocks.push_back(b);
    }

    scanf("%d", &q);
    for (int qq = 1; qq <= q; qq++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int i, j; scanf("%d %d", &i, &j); i--, j--;
        // update
        if (posToBlock[i] != posToBlock[j])
        {
          blocks[posToBlock[i]].erase(a[i]);
          blocks[posToBlock[i]].insert(a[j]);

          blocks[posToBlock[j]].erase(a[j]);
          blocks[posToBlock[j]].insert(a[i]);
        }

        swap(a[i], a[j]);
      }
      else
      {
        int l, r, x; scanf("%d %d %d", &l, &r, &x); l--, r--, x--;

        int ans = op == 2 ? 1e9 : -1e9;
        for (int i = posToBlock[l] + 1; i < posToBlock[r]; i++)
        {
          if (op == 2)
          {
            auto it = blocks[i].values.lower_bound(x);
            if (it != blocks[i].values.end()) ans = min(ans, *it);
          }
          else
          {
            auto it = blocks[i].nvalues.lower_bound(-x);
            if (it != blocks[i].nvalues.end()) ans = max(ans, -(*it));
          }
        }

        for (int i = l, endB = posToBlock[l]; i <= r && posToBlock[i] == endB; i++)
          updateAns(ans, op, a[i], x);
        for (int i = r, endB = posToBlock[r]; i >= l && posToBlock[i] == endB; i--)
          updateAns(ans, op, a[i], x);

        if (ans < 0 || ans > n) ans = -2;
        printf("%d\n", ans + 1);
        // printf("%d - %d - %d %d %d - %d\n", qq, op, l + 1, r + 1, x + 1, ans + 1);
      }
    }
  }
  return 0;
}
