#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[11], t[12];
  while (scanf(" %s %s", s, t) != EOF)
  {
    t[strlen(s)] = '\0';
    printf("%s\n", !strcmp(s, t) ? "Yes" : "No");
  }
  return 0;
}