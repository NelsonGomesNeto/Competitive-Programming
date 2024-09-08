#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; scanf("%d", &n);
    vector<int> ans;
    for (int i = 0, p = 1; i < 5; i++, p *= 10)
    {
      if (n % 10 != 0)
        ans.push_back(p * (n % 10));
      n /= 10;
    }
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
      printf("%d%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
