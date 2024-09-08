#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int kMaxN = 100;
int n;
int d[kMaxN];

int Digits(int x) {
  int mask = 0;
  while (x) {
    mask |= (1LL << (x % 10));
    x /= 10;
  }
  return mask;
}

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; ++i)
      scanf("%d", &d[i]);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= d[i - 1]; ++j) {
        if (Digits(i) == Digits(j) && __builtin_popcount(Digits(i)) == 1) {
          ++ans;
          DEBUG printf("\t%d %d | %d\n", i, j, Digits(i));
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
