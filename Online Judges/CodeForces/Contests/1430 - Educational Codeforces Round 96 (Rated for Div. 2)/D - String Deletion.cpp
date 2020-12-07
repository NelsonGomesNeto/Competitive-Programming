#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];
bool deleted[maxN];

struct Block
{
  int lo, hi;
  int size() { return hi - lo + 1; }
};
vector<Block> blocks;

int removePrefix(int from)
{
  int j = from;
  while (j + 1 < n && (deleted[j + 1] || s[j + 1] == s[from]))
    deleted[j++] = true;
  return j + 1;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      scanf(" %s", s);
      memset(deleted, false, sizeof(deleted));

      blocks.clear();
      for (int i = 0; i < n; i++)
      {
        int j = i;
        while (j + 1 < n && s[i] == s[j + 1]) j++;
        if (j - i + 1 >= 2)
          blocks.push_back(Block{i, j});
        i = j;
      }

      int ans = 0, now = 0;
      for (Block &block: blocks)
      {
        while (block.size() >= 2 && block.lo >= now)
        {
          deleted[block.lo] = true;
          now = removePrefix(now + (block.lo == now));
          block.lo++;
          ans++;
        }
      }
      while (now < n)
      {
        now = removePrefix(now + 1);
        ans++;
      }

      DEBUG printf("%d (%s) - %d\n", tt, s, ans);
      else printf("%d\n", ans);
    }
  return 0;
}
