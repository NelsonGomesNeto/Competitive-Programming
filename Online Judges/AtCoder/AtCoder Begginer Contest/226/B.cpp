#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
vector<int> sqs[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      sqs[i].clear();
      int sz; scanf("%d", &sz);
      sqs[i].resize(sz);
      for (int j = 0; j < sz; j++)
        scanf("%d", &sqs[i][j]);
    }
    sort(sqs, sqs+n);

    lli ans = 0;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j + 1 < n && sqs[j + 1] == sqs[i])
        j++;

      ans++;
      i = j;
    }
    printf("%lld\n", ans);
  }
  return 0;
}