#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int s, t, x;
  while (~scanf("%d %d %d", &s, &t, &x))
  {
    bool can = s == x;
    while (s != t)
    {
      s++;
      if (s == 24) s = 0;
      if (s != t)
        can |= s == x;
    }
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}