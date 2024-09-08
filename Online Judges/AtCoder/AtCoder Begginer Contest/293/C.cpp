#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxNum = 10 * 10;
int n, m;
int mat[maxN][maxN];

lli solve(int i = 0, int j = 0, bitset<maxNum + 1> visited = 0)
{
  if (visited[mat[i][j]]) return 0;
  if (i == n - 1 && j == m - 1) return 1;
  visited[mat[i][j]] = true;
  lli ans = 0;
  if (i != n - 1) ans += solve(i + 1, j, visited);
  if (j != m - 1) ans += solve(i, j + 1, visited);
  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    vector<int> numbers;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
      {
        scanf("%d", &mat[i][j]);
        numbers.push_back(mat[i][j]);
      }
    sort(numbers.begin(), numbers.end());
    numbers.resize(distance(numbers.begin(), unique(numbers.begin(), numbers.end())));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        mat[i][j] = lower_bound(numbers.begin(), numbers.end(), mat[i][j]) - numbers.begin();

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
