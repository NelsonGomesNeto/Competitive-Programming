#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
char s[2*maxN + 2];

int main()
{
  while (~scanf(" %s", s))
  {
    for (int i = 0; s[i] && s[i] != '.'; i++)
      printf("%c", s[i]);
    printf("\n");
  }
  return 0;
}