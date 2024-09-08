#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli l[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    lli totalSum = 0;
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &l[i]);
      totalSum += l[i];
    }

    if (totalSum % 2 != 0) printf("N\n");
    else
    {
      lli target = totalSum >> 1LL;

      int lo = 0, mid = 0; lli sum = 0;
      for (mid = 0; mid < n; mid++)
      {
        sum += l[mid];
        if (sum == target) break;
        while (sum > target) sum -= l[lo++];
      }

      if (sum != target)
        printf("N\n");
      else
      {
        DEBUG printf("\t%d %d\n", lo, mid);

        bool can = false;

        int i = lo, j = (mid + 1) % n;
        lli lsum = l[i], rsum = l[j];
        while (lsum != rsum)
        {
          if (lsum < rsum) lsum += l[i = (i + 1) % n];
          else rsum += l[j = (j + 1) % n];

          if (i == mid || (j + 1) % n == lo)
          {
            lsum = 1, rsum = 0;
            break;
          }
        }
        DEBUG printf("\t%d %d - %lld %lld\n", i, j, lsum, rsum);

        can = lsum == rsum;

        printf("%s\n", can ? "Y" : "N");
      }
    }
  }
  return 0;
}