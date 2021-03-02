#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli pot(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans *= x;
    x *= x, y >>= 1LL;
  }
  return ans;
}

char s[6], t[6];
lli cnt[256];

lli getScore(char ss[])
{
  lli score = 0;
  for (lli i = 1; i <= 9; i++)
  {
    lli c = 0;
    for (int j = 0; j < 5; j++)
      if (ss[j] - '0' == i)
        c++;
    score += i * pot(10, c);
  }
  return score;
}

int main()
{
  lli k;
  while (~scanf("%lld", &k))
  {
    scanf(" %s", s);
    scanf(" %s", t);

    for (int i = 1; i <= 9; i++)
      cnt[i] = k;

    for (int i = 0; i < 4; i++)
      cnt[s[i] - '0']--, cnt[t[i] - '0']--;

    lli takWins = 0, aoWins = 0;
    for (int i = 1; i <= 9; i++)
      for (int j = 1; j <= 9; j++)
        if (cnt[i] > 0 && cnt[j] > 0 && (i != j || cnt[i] > 1))
        {
          s[4] = i + '0', t[4] = j + '0';
          lli ways = 0;
          if (i == j)
            ways = cnt[i] * (cnt[i] - 1);
          else
            ways = cnt[i] * cnt[j];

          if (getScore(s) > getScore(t))
            takWins += ways;
          else
            aoWins += ways;
        }

    DEBUG printf("\t%lld %lld | %lld\n", takWins, aoWins, takWins + aoWins);
    printf("%.15Lf\n", (ldouble)takWins / (takWins + aoWins));
  }
  return 0;
}
