#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (~scanf("%d", &t))
  {
    for (int tt = 1; tt <= t; tt++)
    {
      lli n; int k; scanf("%lld %d", &n, &k);
      /*
        lcm(a, b) = a * b / gcd(a, b)
      */

      vector<int> ans;
      DEBUG printf("\t%lld %d\n", n, (int)sqrt(n));
      vector<int> toTest;
      for (int i = 1, end = min(1000LL, (lli)sqrt(n)); i <= end; i++)
        toTest.push_back(i);
      for (int i = n / 2; i >= max(1LL, n / 2 - 1000); i--)
        toTest.push_back(i);

      for (int i = 0; i < k - 3; i++)
        ans.push_back(1);

      n -= k - 3;
      lli prvK = k;
      k = 3;

      for (int i: toTest)
      {
        if (ans.size() == prvK) break;

        // if (n % i == 0)
        {
          lli divisor = i;
          DEBUG printf("\t\there %lld - %d\n", divisor, i);
          for (lli j = 1; j*divisor <= n && j <= k; j++)
            if (k - j == n - j*divisor)
            {
              for (int jj = 0; jj < j; jj++)
                ans.push_back(divisor);
              for (int jj = 0; jj < k - j; jj++)
                ans.push_back(1);
              break;
            }
            else if (n - j*divisor != 0 && k - j == 1 && lcm(j*divisor, n - j*divisor) <= n / 2)
            {
              for (int jj = 0; jj < j; jj++)
                ans.push_back(divisor);
              for (int jj = 0; jj < k - j; jj++)
                ans.push_back(n - j*divisor);
              break;
            }
            else if (n - j*divisor != 0 && k - j != 0 && (n - j*divisor) % (k - j) == 0 && lcm((n - j*divisor) / (k - j), j*divisor) <= n / 2)
            {
              for (int jj = 0; jj < j; jj++)
                ans.push_back(divisor);
              for (int jj = 0; jj < k - j; jj++)
                ans.push_back((n - j*divisor) / (k - j));
              break;
            }
          }
        }


      for (int i = 0; i < ans.size(); i++)
        printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
