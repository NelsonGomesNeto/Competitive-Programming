#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e3; int s;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &s);
    int ans = 1, curr = 1, sum = 1;
    while (sum < s)
    {
      curr += 2;
      sum += curr;
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
