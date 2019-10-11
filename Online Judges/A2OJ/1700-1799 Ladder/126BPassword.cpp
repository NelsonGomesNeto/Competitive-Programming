#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 2; int n, leftLimit, rightLimit;
char s[maxN];
bool has[maxN];

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
}

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    n = strlen(s);

    prefixFunction(s);
    memset(has, false, sizeof(has));
    for (int i = 1; i < n - 1; i ++)
      has[biggestPrefix[i]] = true;

    int k = biggestPrefix[n - 1];
    if (k && !has[k])
      k = biggestPrefix[k - 1];

    if (k == 0) printf("Just a legend\n");
    else
    {
      s[k] = '\0';
      printf("%s\n", s);
    }
  }
  return 0;
}