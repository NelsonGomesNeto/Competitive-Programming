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
    int n; scanf("%d", &n);
    char s[n + 1]; scanf(" %s", s);

    int suf = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      if (s[i] != ')')
        break;
      suf++;
    }
    int rem = n - suf;
    printf("%s\n", suf > rem ? "Yes" : "No");
  }
  return 0;
}
