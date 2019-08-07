#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e3, inf = 1e6; int n;
char s[maxN + 1];
int ss; bool special[maxN];

struct Ans
{
  int pal, spe;
  bool operator<(const Ans &a) const
  {
    // return(pal < a.pal || (pal == a.pal && spe < a.spe));
    return(spe < a.spe || (spe == a.spe && pal < a.pal));
  }
  bool operator>(const Ans &a) const
  {
    return(pal > a.pal || (pal == a.pal && spe > a.spe));
  }
  Ans operator+(const Ans &a)
  {
    return(Ans({pal + a.pal, spe + a.spe}));
  }
};
Ans memo[maxN][maxN];
Ans solve(int lo = 0, int hi = n - 1, int got = 0)
{
  if (lo >= hi)
  {
    if (!ss) return(Ans({lo == hi, 0}));
    else return(lo == hi ? Ans({1, special[lo]}) : Ans({0, 0}));
  }
  if (memo[lo][hi].pal == -1)
  {
    Ans ans = {0, 0};
    ans = max(ans, solve(lo + 1, hi, got));
    ans = max(ans, solve(lo, hi - 1, got));
    if (s[lo] == s[hi])
      ans = max(ans, solve(lo + 1, hi - 1, got + special[lo] + special[hi]) + Ans({2*(s[lo] == s[hi]), special[lo] + special[hi]}));
    memo[lo][hi] = ans;
  }
  return(memo[lo][hi]);
}

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    memset(special, false, sizeof(special)), n = strlen(s);
    scanf("%d", &ss);
    for (int i = 0, a; i < ss; i ++)
    {
      scanf("%d", &a);
      special[a - 1] = true;
    }
    // printf("%s\n", s);
    // for (int i = 0; i < n; i ++) printf("%d", special[i]); printf("\n");

    memset(memo, -1, sizeof(memo));
    Ans ans = solve();
    printf("%d\n", ans.pal);
  }

  return(0);
}