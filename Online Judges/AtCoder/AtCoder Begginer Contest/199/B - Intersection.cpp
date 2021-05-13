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
    int a[n], b[n];
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%d", &b[i]);

    int ans = 0;
    for (int i = 0; i <= 1000; i++)
    {
      bool valid = true;
      for (int j = 0; j < n; j++)
        if (!(a[j] <= i && i <= b[j]))
          valid = false;
      ans += valid;
    }
    printf("%d\n", ans);
  }
  return 0;
}