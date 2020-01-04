#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m;
int di[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
vector<vector<char>> forest;
vector<vector<int>> acc, acc2;
vector<vector<bool>> onfire;

int getSum(vector<vector<int>> &a, int loi, int loj, int hii, int hij)
{
  loi = max(0, loi), loj = max(0, loj);
  hii = min(n - 1, hii), hij = min(m - 1, hij);
  loi ++, loj ++, hii ++, hij ++;
  return a[hii][hij] - a[loi - 1][hij] - a[hii][loj - 1] + a[loi - 1][loj - 1];
}
bool can(int t)
{
  for (int i = 0; i < n; i ++)
  {
    fill(onfire[i].begin(), onfire[i].end(), false);
    fill(acc2[i].begin(), acc2[i].end(), 0);
  }
  fill(acc2[n].begin(), acc2[n].end(), 0);

  for (int i = t; i < n - t; i ++)
    for (int j = t; j < m - t; j ++)
      if (getSum(acc, i - t, j - t, i + t, j + t) == (2*t+1)*(2*t+1))
        onfire[i][j] = true;
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= m; j ++)
      acc2[i][j] = onfire[i - 1][j - 1] + acc2[i - 1][j] + acc2[i][j - 1] - acc2[i - 1][j - 1];
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      bool gotFire = getSum(acc2, i - t, j - t, i + t, j + t) != 0;
      if ((gotFire && forest[i][j] == '.') || (!gotFire && forest[i][j] == 'X'))
        return false;
    }
  return true;
}
int binarySearch(int lo = 0, int hi = min(n, m))
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (can(mid)) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    forest.clear(), acc.clear(), acc2.clear(), onfire.clear();
    forest.resize(n), acc.resize(n + 1), acc2.resize(n + 1), onfire.resize(n);
    acc[n].resize(m + 1, 0), acc2[n].resize(m + 1, 0);

    char line[m + 1];
    for (int i = 0; i < n; i ++)
    {
      scanf(" %s", line);
      forest[i].resize(m), acc[i].resize(m + 1, 0), acc2[i].resize(m + 1, 0), onfire[i].resize(m);
      for (int j = 0; j < m; j ++)
        forest[i][j] = line[j];
    }
    for (int i = 1; i <= n; i ++)
      for (int j = 1; j <= m; j ++)
        acc[i][j] = (forest[i - 1][j - 1] == 'X') + acc[i - 1][j] + acc[i][j - 1] - acc[i - 1][j - 1];

    int ans = binarySearch();
    can(ans);
    printf("%d\n", ans);
    for (int i = 0; i < n; i ++)
    {
      for (int j = 0; j < m; j ++)
        printf("%c", onfire[i][j] ? 'X' : '.');
      printf("\n");
    }
  }
  return 0;
}
