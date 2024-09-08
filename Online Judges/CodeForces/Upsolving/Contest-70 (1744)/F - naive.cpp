#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
int pos[maxN];
int p[maxN];

int mex(vector<int> &a)
{
  int res = 0;
  for (int aa : a)
    if (aa == res)
      ++res;
  return res;
}

int med(vector<int> &a)
{
  return a[(a.size() - 1) >> 1];
}

int main()
{
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &p[i]);
      pos[p[i]] = i;
    }

    DEBUG {
      printf("p:");
      for (int i = 0; i < n; ++i) printf(" %d", p[i]);
      printf("\n");
    }

    lli ans = 0;
    for (int i = 0; i < n; ++i)
    {
      for (int j = i; j < n; ++j)
      {
        vector<int> now;
        for (int k = i; k <= j; ++k)
          now.push_back(p[k]);
        sort(now.begin(), now.end());
        if (mex(now) > med(now))
        {
          ++ans;
          DEBUG printf("\t%d %d\n", i, j);
        }
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
