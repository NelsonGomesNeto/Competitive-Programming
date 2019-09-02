#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
lli ans[2*maxN];

int main()
{
  scanf("%d", &n);

  for (int i = 0, lo = 1, hi = 2*n, turn = 1; i < n; i ++, turn = !turn)
  {
    if (turn)
    {
      ans[i] = lo, ans[i + n] = lo + 1;
      lo += 2;
    }
    else
    {
      ans[i] = hi, ans[i + n] = hi - 1;
      hi -= 2;
    }
  }

  bool valid = true;
  lli s = 0; for (int i = 0; i < n; i ++) s += ans[i];
  set<lli> sums; sums.insert(s);
  for (int i = 0, end = 2*n + 1; i < end; i ++)
  {
    s = s - ans[i % (2*n)] + ans[(i + n) % (2*n)];
    sums.insert(s);
  }
  valid = sums.size() <= 2;
  if (valid)
  {
    printf("YES\n");
    for (int i = 0, end = 2*n; i < end; i ++)
      printf("%lld%c", ans[i], i < end - 1 ? ' ' : '\n');
  }
  else printf("NO\n");

  return(0);
}
