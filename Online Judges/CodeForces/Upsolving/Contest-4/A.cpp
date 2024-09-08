#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char ans[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    if (n == 1) printf("-1\n");
    else
    {
      for (int i = 0; i < n - 1; i++)
        ans[i] = '9';
      ans[n - 1] = '8', ans[n] = '\0';
      printf("%s\n", ans);
    }
  }
  return 0;
}
