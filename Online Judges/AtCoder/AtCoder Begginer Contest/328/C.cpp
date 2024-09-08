#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 3e5;
int n, q;
char s[kMaxN + 1];
int acc[kMaxN + 1];

int main() {
  while (~scanf("%d %d", &n, &q)) {
    scanf(" %s", s);

    for (int i = 0; i + 1 < n; ++i) {
      acc[i + 1] = acc[i] + (s[i] == s[i + 1]);
    }

    for (int i = 0; i < q; ++i) {
      int l, r;
      scanf("%d %d", &l, &r);
      --l, --r;
      int ans = acc[r] - acc[l];
      printf("%d\n", ans);
    }
  }
  return 0;
}
