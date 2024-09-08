#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
char s[maxN + 1];

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    n = strlen(s);
    printf("%c%d%c\n", s[0], n - 2, s[n - 1]);
  }
  return 0;
}