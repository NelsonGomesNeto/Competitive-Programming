#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 2; int n, leftLimit, rightLimit;
char s[maxN];
bool has[maxN];

int pi[maxN];
void prefixFunction(char str[], int strSize)
{
  pi[0] = -1;
  for (int i = 0, j = -1; i < strSize;)
  {
    while (j >= 0 && str[i] != str[j]) j = pi[j];
    pi[++ i] = ++ j;
  }
}

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);

    prefixFunction(s, n);
    memset(has, false, sizeof(has));
    for (int i = 1; i < n - 1; i ++)
      has[pi[i + 1]] = true;

    int k = pi[n];
    if (k && !has[k])
      k = pi[k];

    if (k == 0) printf("Just a legend\n");
    else
    {
      s[k] = '\0';
      printf("%s\n", s);
    }
  }
  return 0;
}