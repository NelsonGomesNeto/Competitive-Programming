#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 101;
char s[maxN];

int main()
{
  while (scanf("%s", s) != EOF)
  {
    getchar();
    int n = strlen(s), ans = 0;
    for (int i = 0, j = n - 1; i < j; i ++, j --)
      if (s[i] != s[j])
        ans ++;
    printf("%d\n", ans);
  }
  return 0;
}