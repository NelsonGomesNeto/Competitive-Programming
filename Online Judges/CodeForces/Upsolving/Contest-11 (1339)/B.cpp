#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);

    int lo = 0, hi = n - 1; bool turn = true;
    vector<lli> ans;
    while (lo <= hi)
    {
      if (turn) ans.push_back(a[lo++]);
      else ans.push_back(a[hi--]);
      turn = !turn;
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; i++)
      printf("%lld%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}
