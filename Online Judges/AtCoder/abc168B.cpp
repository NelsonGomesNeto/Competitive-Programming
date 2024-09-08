#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int k; char s[101];
  while (scanf("%d %s", &k, s) != EOF)
  {
    if (strlen(s) <= k) printf("%s\n", s);
    else
    {
      s[k] = '\0';
      printf("%s...\n", s);
    }
  }
  return 0;
}