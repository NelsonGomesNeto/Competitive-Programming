#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, x;
char s[maxN + 1];

int main()
{
  while (scanf("%d %d", &n, &x) != EOF)
  {
    scanf(" %s", s);
    for (int i = 0; i < n; i++)
      if (s[i] == 'o')
        x++;
      else
        x = max(0, x - 1);
    printf("%d\n", x);
  }
  return 0;
}