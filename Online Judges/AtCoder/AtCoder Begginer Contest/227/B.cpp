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
      int s; scanf("%d", &s);
      bool can = false;
      for (int a = 1; 3*a <= s; a++)
      {
        int rem = s - 3*a;
        if (rem % (3 + 4*a) == 0)
        {
          int b = rem / (3 + 4*a);
          if (b > 0)
            can = true;
        }
      }
      ans += can;
    }
    printf("%d\n", n - ans);
  }
  return 0;
}