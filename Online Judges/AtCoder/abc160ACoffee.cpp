#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char s[7];
  while (scanf(" %s", s) != EOF)
  {
    bool is = true;
    if (s[2] != s[3]) is = false;
    if (s[4] != s[5]) is = false;
    printf("%s\n", is ? "Yes" : "No");
  }
  return 0;
}