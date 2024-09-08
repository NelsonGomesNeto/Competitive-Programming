#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5; int n;
map<int, set<int>> cnt;
set<int> ans;
bool removed[maxN + 1];

void add(int a, int b)
{
  cnt[a].insert(b);
  if (cnt[a].size() == 2)
    ans.insert(a);
}

void remove(int num)
{
  list<int> toRemove;
  if (!cnt.count(num)) return;
  for (int i: cnt[num])
  {
    toRemove.push_back(i);
    if (!removed[i])
    {
      removed[i] = true;
      break;
    }
  }
  for (int i: toRemove)
    cnt[num].erase(i);

  if (cnt[num].size() <= 1)
    ans.erase(num);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(removed, false, sizeof(removed));
    for (int i = 2; i <= n; i++)
    {
      for (int j = 2, end = sqrt(i); j <= end; j++)
      {
        if (i % j == 0)
        {
          add(j, i);
          if (i / j != j && i % (i / j) == 0)
            add(i / j, i);
        }
      }
      add(i, i);
    }
    ans.insert(1);
    continue;

    vector<int> lol;
    for (int i = 0; i < n - 1; i++)
    {
      lol.push_back(*ans.rbegin());
      remove(*ans.rbegin());
    }
    reverse(lol.begin(), lol.end());
    for (int i = 0; i < n - 1; i++)
      printf("%d%c", lol[i], i < n - 2 ? ' ' : '\n');
  }
  return 0;
}