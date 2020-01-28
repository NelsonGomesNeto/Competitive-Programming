#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char ans[maxN + 1];
int a[maxN];
int pos[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      ans[i] = '0';
      scanf("%d", &a[i]);
      pos[a[i] - 1] = i;
    }
    ans[n] = '\0';

    set<int> all;
    for (int i = 0; i < n; i ++)
    {
      all.insert(pos[i]);
      if (all.size() == *all.rbegin() - *all.begin() + 1)
        ans[i] = '1';
    }

    printf("%s\n", ans);
  }
  return 0;
}
