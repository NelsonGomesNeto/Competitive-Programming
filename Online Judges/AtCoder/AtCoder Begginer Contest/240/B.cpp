#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
set<int> a;

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      int aa; scanf("%d", &aa);
      a.insert(aa);
    }
    printf("%d\n", (int)a.size());
  }
  return 0;
}