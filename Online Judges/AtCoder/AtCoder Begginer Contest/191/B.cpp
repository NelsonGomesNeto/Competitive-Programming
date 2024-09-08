#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x;
lli a[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &x))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    vector<lli> ans;
    for (int i = 0; i < n; i++)
      if (a[i] != x)
        ans.push_back(a[i]);

    for (int i = 0; i < ans.size(); i++)
      printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}