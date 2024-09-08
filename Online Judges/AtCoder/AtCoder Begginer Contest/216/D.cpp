#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
deque<int> cnt[maxN];
int it[maxN];
vector<int> a[maxN];
int done;

void fix(int c)
{
  DEBUG printf("here %d\n", c); fflush(stdout);
  done++;
  for (int k = 0; k < 2; k++)
  {
    int p = cnt[c][0];
    it[p]++;
    if (it[p] < a[p].size())
    {
      cnt[a[p][it[p]]].push_back(p);
      if (cnt[a[p][it[p]]].size() == 2)
        fix(a[p][it[p]]);
    }
    cnt[c].pop_front();
  }
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < m; i++)
    {
      a[i].clear();
      int k; scanf("%d", &k);
      a[i].resize(k);
      for (int j = 0; j < k; j++)
      {
        scanf("%d", &a[i][j]);
        a[i][j]--;
      }
    }

    for (int i = 0; i < n; i++) cnt[i].clear();
    memset(it, 0, sizeof(it));
    done = 0;

    for (int i = 0; i < m; i++)
      cnt[a[i][it[i]]].push_back(i);

    for (int k = 0; k < 5; k++)
      for (int i = 0; i < n; i++)
        if (cnt[i].size() == 2)
          fix(i);

    printf("%s\n", done == n ? "Yes" : "No");
  }
  return 0;
}