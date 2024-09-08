#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    set<int> a;
    for (int i = 0; i < n; i++)
    {
      int aa; scanf("%d", &aa);
      a.insert(aa);
    }
    printf("%s\n", a.size() == n ? "Yes" : "No");
  }
  return 0;
}