#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int
int n, t, tap[31];
lli now, previ, a0, x, y;

lli next()
{
  previ = now;
  int bit = now & 1;
  for (int i = 1; i < t; i ++) bit ^= (now >> tap[i]) & 1;
  now = (now >> 1) | (bit << (n - 1));
  return(previ);
}

pair<int, int> solve()
{
  int firstApp[x]; memset(firstApp, -1, sizeof(firstApp));
  lli sum = 0; firstApp[0] = 0;
  for (int i = 0; ; i ++)
  {
    lli value = next();
    sum = (sum + value) % x;
    if (firstApp[sum] != -1)
    {
      if (i - firstApp[sum] + 1 >= y) return(make_pair(firstApp[sum], i));
    }
    else
      firstApp[sum] = i + 1;
  }
}

int main()
{
  scanf("%d %d %lld %lld %lld", &n, &t, &a0, &x, &y); now = a0;
  for (int i = 0; i < t; i ++) scanf("%d", &tap[i]);

  pair<int, int> ans = solve();
  printf("%d %d\n", ans.first, ans.second);

  return(0);
}
