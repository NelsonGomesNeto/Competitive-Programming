#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1;
char s[maxN];

int biggestPrefix[maxN];
void prefixFunction(char str[])
{
  biggestPrefix[0] = 0;
  for (int i = 1; str[i]; i ++)
  {
    int j = biggestPrefix[i - 1];
    while (j > 0 && str[i] != str[j]) j = biggestPrefix[j - 1];
    biggestPrefix[i] = j + (str[i] == str[j]);
  }

  DEBUG {
    printf("%s\n", str); int end = min(1000, (int)strlen(str));
    for (int i = 0; i < end; i ++) printf("%3d%c", i, i < end - 1 ? ' ' : '\n');
    for (int i = 0; i < end; i ++) printf("%3d%c", biggestPrefix[i], i < end - 1 ? ' ' : '\n');
  }
}

int main()
{
  scanf("%s", s);
  prefixFunction(s);

  return 0;
}