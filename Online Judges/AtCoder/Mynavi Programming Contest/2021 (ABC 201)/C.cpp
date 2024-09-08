#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[11];
  while (~scanf(" %s", s))
  {
    int ans = 0;
    for (int i = 0; i <= 9999; i++)
    {
      set<int> digits;
      int aux = i;
      for (int j = 0; j < 4; j++)
      {
        digits.insert(aux % 10);
        aux /= 10;
      }

      bool valid = true;

      for (int d: digits)
        if (s[d] == 'x')
          valid = false;

      for (int d = 0; d <= 9; d++)
        if (s[d] == 'o' && !digits.count(d))
          valid = false;

      ans += valid;
    }
    printf("%d\n", ans);
  }
  return 0;
}