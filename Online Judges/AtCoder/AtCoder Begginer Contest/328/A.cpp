#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main() {
  int n, x;
  scanf("%d %d", &n, &x);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int s;
    scanf("%d", &s);
    if (s <= x) ans += s;
  }
  printf("%d\n", ans);
  return 0;
}
