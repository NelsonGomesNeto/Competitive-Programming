#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN + 1];
int cnt[3];
list<pair<int, int>> ops;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    ops.clear();

    if (n == 3)
    {
      printf("2\n3 2\n3 2\n");
      continue;
    }

    int k = min(n - 1, 8);
    for (int i = 3; i < n; i++)
      if (i != k)
        ops.push_back({i, n});

    int last = n;
    while (last > 1)
    {
      ops.push_back({n, k});
      last = last / k + (last % k != 0);
    }
    int mid = k;
    while (mid > 1)
    {
      ops.push_back({k, 2});
      mid = mid / 2 + (mid & 1);
    }

    for (int i = 1; i <= n; i++) a[i] = i;
    for (auto &op: ops)
      a[op.first] = a[op.first] / a[op.second] + (a[op.first] % a[op.second] != 0);

    DEBUG {
      printf("\tn: %d\n", n);
      for (int i = 1; i <= n; i++) if (a[i] != 1) printf("(%d, %d) ", i, a[i]);
      printf("\n");
      fflush(stdout);
    }

    cnt[1] = cnt[2] = 0;
    for (int i = 1; i <= n; i++)
    {
      assert(a[i] >= 1 && a[i] <= 2);
      cnt[a[i]]++;
    }
    assert(cnt[1] == n - 1);
    assert(cnt[2] == 1);
    assert(ops.size() <= n + 5);

    printf("%d\n", (int)ops.size());
    for (auto &op: ops)
      printf("%d %d\n", op.first, op.second);
  }
  return 0;
}