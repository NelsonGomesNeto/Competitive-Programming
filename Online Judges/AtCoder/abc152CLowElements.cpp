#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int p[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    int ans = 0;
    set<int> all;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &p[i]);
      p[i] --;
      all.insert(p[i]);
      ans += *all.begin() == p[i];
    }

    printf("%d\n", ans);
  }
  return 0;
}