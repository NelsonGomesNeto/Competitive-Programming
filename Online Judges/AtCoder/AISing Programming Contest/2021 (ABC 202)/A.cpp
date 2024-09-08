#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int d[3];
  int ans = 0;
  for (int i = 0; i < 3; i++)
  {
    scanf("%d", &d[i]);
    ans += 7 - d[i];
  }
  printf("%d\n", ans);
  return 0;
}