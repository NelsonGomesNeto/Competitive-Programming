#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 2e5;
int n, m;
int a[kMaxN];

int main() {
  while (~scanf("%d %d", &n, &m)) {
    for (int i = 0; i < m; ++i) {
      scanf("%d", &a[i]);
      --a[i];
    }

    sort(a, a+m);

    for (int i = 0; i < n; ++i) {
      int ans = a[lower_bound(a, a+m, i) - a] - i;
      printf("%d\n", ans);
    }
  }
  return 0;
}
