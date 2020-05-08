#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101, inf = 1e4; int n;
char s[maxN];
int d[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s); n = strlen(s);
    for (int i = 0; i < n; i++)
      d[i] = s[i] - '0';

    printf("Case #%d: ", tt);
    int o = 0;
    for (int i = 0; i < n; i++)
    {
      while (o < d[i]) printf("("), o++;
      while (o > d[i]) printf(")"), o--;
      printf("%d", d[i]);
    }
    while (o) printf(")"), o--;
    printf("\n");
  }
  return 0;
}