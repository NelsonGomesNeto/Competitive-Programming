#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;


int main()
{
  int c; scanf("%d", &c);
  int ans = 100, curr = 100;
  for (int i = 0; i < c; i++)
  {
    int v; scanf("%d", &v);
    curr += v;
    ans = max(ans, curr);
  }
  printf("%d\n", ans);

  return 0;
}