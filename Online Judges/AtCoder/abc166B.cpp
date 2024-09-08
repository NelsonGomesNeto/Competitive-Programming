#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    bool has[n]; memset(has, false, sizeof(has));
    for (int i = 0; i < k; i++)
    {
      int di; scanf("%d", &di);
      for (int j = 0; j < di; j++)
      {
        int aij; scanf("%d", &aij); aij--;
        has[aij] = true;
      }
    }

    int ans = 0; for (int i = 0; i < n; i++) ans += !has[i];
    printf("%d\n", ans);
  }
  return 0;
}