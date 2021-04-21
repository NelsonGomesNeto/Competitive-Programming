#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];
int ans[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %s", &n, s);
    for (int i = 0; i < n; i++)
    {
      int j = i;
      while (j - 1 >= 0 && s[j - 1] < s[j])
        j--;
      ans[i] = i - j + 1;
    }

    printf("Case #%d: ", tt);
    for (int i = 0; i < n; i++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}