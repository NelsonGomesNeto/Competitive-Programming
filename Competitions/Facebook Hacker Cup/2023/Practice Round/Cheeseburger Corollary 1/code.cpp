#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int s, d, k;

int main() {
  int test_cases;
  scanf("%d", &test_cases);

  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%d %d %d", &s, &d, &k);

    const int bun = 2*s + 2*d;
    const int cheese = s + 2*d;
    const int patty = s + 2*d;

    const int required_bun = 2 + (k - 1);
    const int required_cheese = k;
    const int required_patty = k;

    const bool ans = bun >= required_bun && cheese >= required_cheese && patty >= required_patty;
    printf("Case #%d: %s\n", test_case, ans ? "YES" : "NO");
  }
  return 0;
}
