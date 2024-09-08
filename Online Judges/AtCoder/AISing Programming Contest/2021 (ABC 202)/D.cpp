#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
aabb - 1
abab - 2
abba - 3
baab - 4
baba - 5
bbaa - 6

*/

const int maxN = 30;
const lli inf = LONG_LONG_MAX;
int a, b; lli k;

lli memo[maxN + 1][maxN + 1];
lli solve(int aa = a, int bb = b)
{
  if (aa + bb == 0) return 1;
  lli &ans = memo[aa][bb];
  if (ans != -1) return ans;

  ans = 0;
  if (aa) ans += solve(aa - 1, bb);
  if (bb) ans += solve(aa, bb - 1);
  return ans;
}

string build(int aa = a, int bb = b, lli curr = k)
{
  if (aa + bb == 0) return "";

  string ans = "";
  lli putA = aa ? solve(aa - 1, bb) : -1;
  lli putB = bb ? solve(aa, bb - 1) : -1;
  DEBUG printf("\t%d %d %lld | %lld %lld\n", aa, bb, curr, putA, putB);
  if (curr <= putA)
    ans = 'a' + build(aa - 1, bb, curr);
  else
    ans = 'b' + build(aa, bb - 1, curr - (putA >= 0 ? putA : 0));

  return ans;
}

int main()
{
  while (~scanf("%d %d %lld", &a, &b, &k))
  {
    memset(memo, -1, sizeof(memo));
    lli total = solve();
    DEBUG printf("%lld\n", total);

    string ans = build();
    printf("%s\n", ans.c_str());
  }
  return 0;
}