#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[4];
  while (scanf(" %s", s) != EOF)
  {
    printf("%s\n", s[0] != s[1] || s[1] != s[2] ? "Yes" : "No");
  }
  return 0;
}