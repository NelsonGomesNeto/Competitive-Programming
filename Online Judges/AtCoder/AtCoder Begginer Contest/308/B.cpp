#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxS = 20;
int n, m;
char ss[maxS + 1];
string c[maxN];
string d[maxN];
map<string, int> price;

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    price.clear();
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      c[i] = string(ss);
    }
    for (int i = 0; i < m; ++i)
    {
      scanf(" %s", ss);
      d[i] = string(ss);
    }
    int p0;
    scanf("%d", &p0);
    for (int i = 0; i < m; ++i)
    {
      int p;
      scanf("%d", &p);
      price[d[i]] = p;
    }

    int total = 0;
    for (int i = 0; i < n; ++i)
    {
      if (price.count(c[i])) total += price[c[i]];
      else total += p0;
    }
    printf("%d\n", total);
  }
  return 0;
}
