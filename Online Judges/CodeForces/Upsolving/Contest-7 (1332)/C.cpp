#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, k;
char s[maxN + 1];
int cnt[26][maxN];

int memo[maxN];
int solve(int i = 0, int j = k - 1)
{
  if (i > j) return 0;
  if (memo[i] != -1) return memo[i];

  int ans = n;
  for (char letter = 'a'; letter <= 'z'; letter++)
  {
    int cost = (n/k) - cnt[letter - 'a'][i];
    if (i != j) cost += (n/k) - cnt[letter - 'a'][j];
    ans = min(ans, solve(i + 1, j - 1) + cost);
  }
  return memo[i] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %d", &n, &k);
    for (char letter = 'a'; letter <= 'z'; letter++)
      for (int i = 0; i < k; i++)
        cnt[letter - 'a'][i] = 0;
    scanf(" %s", s);

    for (int i = 0; i < n; i += k)
      for (int j = 0; j < k; j++)
        cnt[s[i + j] - 'a'][j]++;

    for (int i = 0; i < n; i++)
      memo[i] = -1;
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
// 123456789
// 12345 56789
// 123 456 789