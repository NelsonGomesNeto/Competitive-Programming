#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[2], t[2];
  while (scanf("%s %s", s, t) != EOF)
  {
    if (s[0] == 'Y') printf("%c\n", toupper(t[0]));
    else printf("%c\n", t[0]);
  }
  return 0;
}