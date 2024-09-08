#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int m, n;
  while (scanf("%d %d", &m, &n) != EOF)
  {
    int a[n], s = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      s += a[i];
    }
    printf("%d\n", s <= m ? m - s : -1);
  }
  return 0;
}