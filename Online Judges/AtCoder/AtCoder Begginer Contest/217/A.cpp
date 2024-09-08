#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
char s[maxN + 1], t[maxN + 1];

int main()
{
  while (~scanf( "%s %s", s, t))
  {
    printf("%s\n", strcmp(s, t) < 0 ? "Yes" : "No");
  }
  return 0;
}