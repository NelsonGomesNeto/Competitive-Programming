#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50;
char s[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf(" %s", s);
    for (int i = 0; s[i]; i++)
      if (i & 1)
      {
        for (char l = 'z'; l >= 'a'; l--)
          if (s[i] != l)
          {
            s[i] = l;
            break;
          }
      }
      else
      {
        for (char l = 'a'; l <= 'z'; l++)
          if (s[i] != l)
          {
            s[i] = l;
            break;
          }
      }
    printf("%s\n", s);
  }
  return 0;
}
