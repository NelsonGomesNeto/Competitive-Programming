#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1;
char s[maxN], t[maxN];

int main()
{
  while (scanf(" %s %s", s, t) != EOF)
  {
    int ans = 0;
    for (int i = 0; s[i]; i++)
      ans += s[i] != t[i];
    printf("%d\n", ans);
  }
  return 0;
}