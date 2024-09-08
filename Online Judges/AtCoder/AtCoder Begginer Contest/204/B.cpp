#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      int a; scanf("%d", &a);
      ans += max(0, a - 10);
    }
    printf("%d\n", ans);
  }
  return 0;
}