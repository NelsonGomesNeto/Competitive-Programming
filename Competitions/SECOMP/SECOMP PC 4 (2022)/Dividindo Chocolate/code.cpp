#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m;
  while (~scanf("%d %d", &n, &m))
  {
    int ans = n / m;
    printf("%d\n", ans);
  }
  return 0;
}
