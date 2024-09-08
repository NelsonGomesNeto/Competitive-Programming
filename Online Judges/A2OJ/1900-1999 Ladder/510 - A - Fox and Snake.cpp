#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n, m;
char ans[maxN][maxN + 1];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(ans, '\0', sizeof(ans));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) ans[i][j] = '.';

    for (int i = 0; i < n; i += 2)
    {
      for (int j = 0; j < m; j++)
        ans[i][j] = '#';
      if (i + 1 < n)
        ans[i + 1][(i >> 1) & 1 ? 0 : m - 1] = '#';
    }

    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i]);
  }
  return 0;
}