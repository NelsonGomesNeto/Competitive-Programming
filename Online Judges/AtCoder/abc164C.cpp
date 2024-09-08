#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

char ss[101];

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    set<string> items;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", ss);
      items.insert(string(ss));
    }
    printf("%d\n", (int)items.size());
  }
  return 0;
}