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
    int n; scanf("%d", &n);
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];

    vector<int> divisors = {1, sum};
    for (int i = 2, end = sqrt(sum); i <= end; i++)
      if (sum % i == 0)
      {
        divisors.push_back(i);
        if (sum % (sum / i) == 0 && sum / i != i)
          divisors.push_back(sum / i);
      }

    int ans = n;
    for (int d: divisors)
      if (d <= n)
      {
        bool valid = true;
        int divisions = 0, target = sum / d;
        DEBUG printf("\t%d %d\n", d, target);
        for (int i = 0; i < n; i++)
        {
          int j = i, curr = a[i];
          while (j + 1 < n && curr < target)
            curr += a[++j];

          if (curr != target)
            valid = false;

          i = j;
          divisions++;
        }
        valid &= d == divisions;
        if (valid)
          ans = min(ans, n - d);
      }
    printf("%d\n", ans);
  }
  return 0;
}
