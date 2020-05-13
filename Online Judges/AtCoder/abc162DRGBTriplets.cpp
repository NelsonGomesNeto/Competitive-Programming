#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4e3; int n;
char s[maxN + 1];
char letters[4] = "RGB";
int acc[3][maxN + 1];

int rem(int i, int j, int l)
{
  int m = j - i + j;
  if (m < n)
    return s[m] == letters[l];
  return 0;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);
    for (int l = 0; l < 3; l++)
      for (int i = 0; i < n; i++)
        acc[l][i + 1] = acc[l][i] + (s[i] == letters[l]);

    lli ans = 0;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (s[i] != s[j])
          for (int l = 0; l < 3; l++)
            if (s[i] != letters[l] && s[j] != letters[l])
            {
              DEBUG printf("\t%d %d %c - %d\n", i, j, letters[l], acc[l][n] - acc[l][j]);
              ans += max(0, acc[l][n] - acc[l][j] - rem(i, j, l));
            }

    printf("%lld\n", ans);
  }
  return 0;
}