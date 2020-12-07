#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 50; int n, m;
int A[maxN][maxN], B[maxN][maxN];

bool valid(int i, int j)
{
  bool can = A[i][j] + A[i][j + 1] + A[i + 1][j] + A[i + 1][j + 1] == 4;
  if (can)
    B[i][j] = B[i][j + 1] = B[i + 1][j] = B[i + 1][j + 1] = 1;
  return can;
}

bool possible()
{
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      if (A[i][j] != B[i][j])
        return false;
  return true;
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &A[i][j]);

  vector<pair<int, int>> ans;
  for (int i = 0; i < n - 1; i ++)
    for (int j = 0; j < m - 1; j ++)
      if (valid(i, j))
        ans.push_back({i + 1, j + 1});

  if (possible())
  {
    printf("%d\n", (int)ans.size());
    for (auto p: ans)
      printf("%d %d\n", p.first, p.second);
  }
  else printf("-1\n");

  return(0);
}