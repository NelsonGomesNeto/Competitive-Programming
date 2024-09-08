#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n;
char incoming[maxN + 1], outgoing[maxN + 1];
char ans[maxN][maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %s %s", &n, incoming, outgoing);
    DEBUG printf("%d - %s - %s\n", n, incoming, outgoing);

    memset(ans, '\0', sizeof(ans));
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
      {
        int u = i, v = j;
        ans[i][j] = 'Y';
        if (u < v)
          while (u < v)
          {
            if (incoming[u + 1] == 'N' || outgoing[u] == 'N')
              ans[i][j] = 'N';
            u++;
          }
        else if (u > v)
          while (u > v)
          {
            if (incoming[u - 1] == 'N' || outgoing[u] == 'N')
              ans[i][j] = 'N';
            u--;
          }
      }

    printf("Case #%d: \n", tt);
    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i]);
  }
  return 0;
}