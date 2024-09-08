#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxZ = 1e5;
const lli inf = 1e13;

int n;
struct District {
  int x, y, z;
  void read() {
    scanf("%d %d %d", &x, &y, &z);
  }
  bool taka() {
    return x > y;
  }
  int result() {
    if (x > y) return z;
    else return -z;
  }
  lli convince() {
    return (y - x + 1) >> 1;
  }
};
District districts[maxN];

lli memo[maxN][2*maxZ + 1];
lli solve(int i = 0, int z_diff = 0) {
  if (i == n) return z_diff > 0 ? 0 : inf;
  lli& ans = memo[i][z_diff + maxZ];
  if (ans != -1) return ans;

  ans = solve(i + 1, z_diff + districts[i].result());
  if (!districts[i].taka()) {
    ans = min(ans, solve(i + 1, z_diff - districts[i].result()) + districts[i].convince());
  }

  return ans;
}

int main()
{
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i)
      districts[i].read();

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
