#include <bits/stdc++.h>
using namespace std;

int main()
{
  // vector<int> divisors;
  // for (int i = 1; i <= )

  int D; scanf("%d", &D);
  int a, b, c, d;
  for (a = -1000; a <= 1000; a ++)
  {
    if (a == 0) continue;
    for (d = -1000; d <= 1000; d ++)
      if (a != d)
      {
        int target = abs(a*d - D);
        for (int j = sqrt(target); j >= 1; j --)
          if (target % j == 0)
          {
            b = j, c = target / j;
            if (b < -1000 || b > 1000 || c < -1000 || c > 1000) continue;
            if (b != c && a != b && a != c && b != d && c != d && a*d - b*c == D)
            {
              printf("%d %d\n%d %d\n", a, b, c, d);
              return(0);
            }
          }
      }
  }
  return(0);
}