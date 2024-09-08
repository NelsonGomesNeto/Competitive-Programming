#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int n, k;
int s[maxN];
int cnt[maxN + 1];

int main() {
  int testCases; scanf("%d", &testCases);
  for (int testCase = 1; testCase <= testCases; ++testCase) {
    fill(cnt, cnt+maxN+1, 0);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i) scanf("%d", &s[i]);

    for (int i = 0; i < n; ++i)
      ++cnt[s[i]];

    bool can = n <= k * 2;
    for (int i = 0; i <= maxN; ++i)
      if (cnt[i] > 2)
        can = false;
    printf("Case #%d: %s\n", testCase, can ? "YES" : "NO");
  }
  return 0;
}
