#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    int n, m, a, b;
    scanf("%d %d %d %d", &n, &m, &a, &b);
    // I'm not confident that this is the actual solution haha.
    // But my tests point that this really is the solution hehe.
    bool ans = n > m;
    printf("Case #%d: %s\n", test_case, ans ? "YES" : "NO");
  }
  return 0;
}
