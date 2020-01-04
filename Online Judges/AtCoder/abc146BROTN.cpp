#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxS = 1e4 + 1;
char s[maxS];

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);
    for (int i = 0; s[i]; i ++)
      s[i] = ((s[i] - 'A') + n) % 26 + 'A';
    printf("%s\n", s);
  }
  return 0;
}