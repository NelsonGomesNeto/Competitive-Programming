#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxQ = 50;
int n, m, q;
int a[maxQ], b[maxQ], c[maxQ], d[maxQ];
int A[maxN];

int solve(int i = 0, int prv = 1)
{
  if (i == n)
  {
    int ans = 0;
    for (int j = 0; j < q; j++)
      if (A[b[j]] - A[a[j]] == c[j])
        ans += d[j];
    return ans;
  }
  int ans = 0;
  for (int aa = prv; aa <= m; aa++)
  {
    A[i] = aa;
    ans = max(ans, solve(i + 1, aa));
  }
  return ans;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &q) != EOF)
  {
    for (int i = 0; i < q; i++)
    {
      scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
      a[i]--, b[i]--;
    }
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}