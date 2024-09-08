#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
char mat[maxN][maxN + 1];
int ans[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
      scanf(" %s", mat[i]);

    for (int j = 0; j < m; ++j)
    {
      ans[j] = 0;
      for (int i = 0; i < n; ++i)
        ans[j] += mat[i][j] == '#';
    }

    for (int i = 0; i < m; ++i)
      printf("%d%c", ans[i], i + 1 < m ? ' ' : '\n');
  }
  return 0;
}
