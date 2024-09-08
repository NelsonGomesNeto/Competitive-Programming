#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[20];
  while (~scanf(" %[^\n]", s))
  {
    printf("%s\n", !strcmp(s, "Hello,World!") ? "AC" : "WA");
  }
  return 0;
}