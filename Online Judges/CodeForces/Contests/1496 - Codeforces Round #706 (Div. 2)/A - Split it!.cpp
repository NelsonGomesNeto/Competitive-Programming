#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n, k; scanf("%d %d", &n, &k);
    char s[n + 1]; scanf(" %s", s);
    bool can = true;
    for (int i = 0, j = n - 1; i < k; i++, j--)
      if (s[i] != s[j] || i >= j || abs(j - i) <= 1)
        can = false;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
