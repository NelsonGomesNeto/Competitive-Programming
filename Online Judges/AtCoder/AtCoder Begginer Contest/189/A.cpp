#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  char c[4];
  while (~scanf(" %s", c))
  {
    printf("%s\n", c[0] == c[1] && c[1] == c[2] ? "Won" : "Lost");
  }
  return 0;
}