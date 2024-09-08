#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[2][3];
  while (~scanf(" %s", s[0]))
  {
    scanf(" %s", s[1]);

    bool can = true;
    if (!strcmp(s[0], ".#") && !strcmp(s[1], "#."))
      can = false;
    if (!strcmp(s[0], "#.") && !strcmp(s[1], ".#"))
      can = false;
    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}