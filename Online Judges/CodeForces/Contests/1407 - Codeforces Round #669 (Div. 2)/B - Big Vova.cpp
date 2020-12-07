#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
int a[maxN];
vector<int> ans;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
      sort(a, a+n, greater<int>());

      ans.clear();
      ans.push_back(a[0]);
      int g = a[0];
      a[0] = -1;
      for (int i = 1; i < n; i++)
      {
        int bestG = 1, bestIndex = -1;
        for (int j = 0; j < n; j++)
          if (a[j] != -1 && gcd(g, a[j]) >= bestG)
            bestG = gcd(g, a[j]), bestIndex = j;
        assert(bestIndex != -1);
        ans.push_back(a[bestIndex]);
        g = gcd(g, ans.back());
        a[bestIndex] = -1;
      }

      for (int i = 0; i < n; i++)
        printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}
