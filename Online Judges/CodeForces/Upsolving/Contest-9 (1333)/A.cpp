#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n, m; scanf("%d %d", &n, &m);
    char ans[n][m + 1];
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        ans[i][j] = 'B';
      ans[i][m] = '\0';
    }
    ans[0][0] = 'W', ans[0][1] = ans[1][0] = 'B';

    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i]);
  }
  return 0;
}
