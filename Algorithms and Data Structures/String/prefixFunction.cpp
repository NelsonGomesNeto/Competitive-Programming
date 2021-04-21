#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tricks with Prefix Function:
  Biggest Palindrome in Prefix: a + '#' + rev(a)
*/

const int maxN = 1e6 + 1; int n;
char s[maxN];

int pi[maxN];
void prefixFunction(char str[], int strSize)
{
  pi[0] = -1;
  for (int i = 0, j = -1; i < strSize;)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++i] = ++ j;
  }
}

int main()
{
  scanf("%s", s);
  n = strlen(s);
  prefixFunction(s, n);
  printf("%s\n", s);
  printf("    "); for (int i = 0; i <= n; i ++) printf("  %c%c", s[i], i < n ? ' ' : '\n');
  for (int i = 0; i <= n; i ++) printf("%3d%c", i, i < n ? ' ' : '\n');
  for (int i = 0; i <= n; i ++) printf("%3d%c", pi[i], i < n ? ' ' : '\n');

  return 0;
}