#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, k, r, s, p;
char t[2*maxN + 1];
bool safe[maxN];

int getValue(char hand)
{
  if (hand == 'r')
    return p;
  else if (hand == 's')
    return r;
  else
    return s;
}

int memo[maxN];
int solve(int i = 0)
{
  if (i >= n) return 0;
  if (memo[i] != -1) return memo[i];
  int ans = max(solve(i + k * (1 + (t[i] == t[i + k]))) + getValue(t[i]), solve(i + k));
  return memo[i] = ans;
}

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    memset(safe, false, sizeof(safe));
    memset(t, '\0', sizeof(t));
    scanf("%d %d %d", &r, &s, &p);
    scanf(" %s", t);

    memset(memo, -1, sizeof(memo));
    lli ans = 0;
    for (int i = 0; i < k; i++)
      ans += solve(i);
    // for (int i = 0; i < n; i++)
    //   ans += getValue(t[i]);

    // for (int i = 0; i + k < n; i++)
    //   if (!safe[i] && t[i] == t[i + k])
    //   {
    //     ans -= getValue(t[i]);
    //     safe[i + k] = true;
    //   }

    printf("%lld\n", ans);
  }
  return 0;
}