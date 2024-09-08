#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 1e5;
int n;
map<lli, lli> slimes;

int main() {
  while (~scanf("%d", &n)) {
    slimes.clear();
    for (int i = 0; i < n; ++i) {
      lli s, c;
      scanf("%lld %lld", &s, &c);
      slimes[s] = c;
    }

    // for (int i = 0; i < 2; ++i)
    for (auto [s, c] : slimes) {
      if (c > 1) {
        slimes[s] = c & 1;
        slimes[2*s] += c >> 1;
      }
    }
    lli ans = 0;
    for (auto [s, c] : slimes) {
      ans += c;
      DEBUG printf("\t%lld %lld\n", s, c);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
