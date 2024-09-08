#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  char s[21];
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", s);
      if (strlen(s) == 3)
      {
        if (s[0] == 'O' && s[1] == 'B') s[2] = 'I';
        if (s[0] == 'U' && s[1] == 'R') s[2] = 'I';
      }
      printf("%s%c", s, i == n - 1 ? '\n' : ' ');
    }
  }
  return 0;
}