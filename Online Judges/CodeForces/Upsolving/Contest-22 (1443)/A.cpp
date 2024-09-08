#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 0; tt < t; tt++)
    {
      int n; scanf("%d", &n);
      vector<int> ans;
      for (int i = 0; i < n; i++)
        ans.push_back(4*n - 2*i);
      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
  }
  return 0;
}
