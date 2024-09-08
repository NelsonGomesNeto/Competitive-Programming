#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int x; scanf("%d", &x);
    vector<int> digits = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    lli ans = 1e18;
    do
    {
      int sum = 0;
      lli curr = 0;
      for (int i = 0; i < digits.size(); i++)
      {
        curr = curr*10 + digits[i];
        sum += digits[i];
        if (sum >= x)
        {
          if (sum == x) ans = min(ans, curr);
          break;
        }
      }
    }
    while (next_permutation(digits.begin(), digits.end()));

    ans = ans == 1e18 ? -1 : ans;
    printf("%lld\n", ans);
  }
  return 0;
}
