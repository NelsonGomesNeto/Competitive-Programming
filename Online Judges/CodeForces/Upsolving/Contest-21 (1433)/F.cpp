#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 70, maxSelected = 70 >> 1, maxK = 70; int n, m, k;
const int inf = 1e6;
vector<vector<int>> a;

int memo[maxN][maxN][maxSelected + 1][maxK + 1];
int rems[maxN][maxN][maxSelected + 1][maxK + 1];
int solve(int i = 0, int j = 0, int selected = 0, int sum = 0)
{
  int rem = sum % k;
  int div = sum / k;

  if (i == n) return rem == 0 ? div : 0;
  int &ans = memo[i][j][selected][rem];
  int &divs = rems[i][j][selected][rem];
  if (div <= divs) return ans;
  divs = div;

  ans = 0;
  if (selected + 1 <= m >> 1)
    ans = max(ans, solve(i + (j == m - 1), (j + 1) % m, j == m - 1 ? 0 : selected + 1, sum + a[i][j]));
  ans = max(ans, solve(i + (j == m - 1), (j + 1) % m, j == m - 1 ? 0 : selected, sum));

  return ans;
}

int solve2(int i = 0, int j = 0, int selected = 0, int kk = 0)
{
  if (i == n) return kk == 0 ? 0 : -inf;
  int &ans = memo[i][j][selected][kk];
  if (ans != -1) return ans;

  ans = solve2(i + (j == m - 1), (j + 1) % m, j == m - 1 ? 0 : selected, kk);
  if (selected + 1 <= m >> 1)
    ans = max(ans, solve2(i + (j == m - 1), (j + 1) % m, j == m - 1 ? 0 : selected + 1, (kk + a[i][j]) % k) + a[i][j]);

  return ans;
}

int main()
{
  int tt = 0;
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
      a[i].resize(m);
      for (int j = 0; j < m; j++)
        scanf("%d", &a[i][j]);
      // sort(a[i].begin(), a[i].end(), greater<int>());
    }
    // sort(a.begin(), a.end(), greater<vector<int>>());

    memset(rems, -1, sizeof(rems));
    memset(memo, -1, sizeof(memo));
    int ans = solve2();
    printf("%d\n", ans);
  }
  return 0;
}
