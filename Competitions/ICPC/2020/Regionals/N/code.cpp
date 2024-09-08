#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli read()
{
  char lol[11];
  lli a, b;
  scanf(" %s", lol);
  sscanf(lol, "$%lld.%lld", &a, &b);
  DEBUG printf("\t%lld %lld\n", a, b);
  return a*100 + b;
}

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    lli balance = read();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      balance += read();
      if (balance % 100 != 0)
        ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
