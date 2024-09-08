#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101; int n;
char ans[maxN][maxN + 1];

int main()
{
  while (~scanf("%d", &n))
  {
    memset(ans, '\0', sizeof(ans));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ans[i][j] = '*';

    for (int i = 0; i <= (n >> 1); i++)
      for (int j = 0; j <= 2*i; j++)
        ans[i][(n >> 1) - i + j] = ans[n - i - 1][(n >> 1) - i + j] = 'D';

    for (int i = 0; i < n; i++)
      printf("%s\n", ans[i]);
  }
  return 0;
}