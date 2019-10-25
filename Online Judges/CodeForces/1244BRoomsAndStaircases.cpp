#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d\n%s", &n, s);
    int ans = n;
    for (int i = 0; i < n; i ++)
      if (s[i] == '1')
        ans = max(ans, 2*(i + 1));
    reverse(s, s+n);
    int ans2 = n;
    for (int i = 0; i < n; i ++)
      if (s[i] == '1')
        ans2 = max(ans2, 2*(i + 1));
    printf("%d\n", max(ans, ans2));
  }
  return 0;
}
