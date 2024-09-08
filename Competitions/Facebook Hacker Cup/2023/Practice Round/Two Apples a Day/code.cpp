#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
1 2 3 5 6

1 1 1 4 6 9

1 1 4 6 9 9 10
*/

const int kMaxN = 3e5;
int n;
vector<int> a;

int Can(const int target, bool try_left) {
  int ans = -1;
  bool fixed = false;
  for (int lo = 0, hi = a.size() - 1; lo < hi; ++lo, --hi) {
    int sum = a[lo] + a[hi];
    if (sum == target) continue;

    if (fixed) {
      return -1;
    }

    if (try_left) {
      if (target > a[hi]) {
        ans = target - a[hi];
        --lo;
      } else {
        return -1;
      }
    } else {
      if (target > a[lo]) {
        ans = target - a[lo];
        ++hi;
      } else {
        return -1;
      }
    }

    fixed = true;
  }
  if (!fixed) {
    ans = target > a[n - 1] ? target - a[n - 1] : -1;
  }
  return ans;
}

bool Check(const int target, int lo, int hi) {
  for (; lo < hi; ++lo, --hi) {
    int sum = a[lo] + a[hi];
    if (sum != target) return false;
  }
  return true;
}

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%d", &n);
    a.resize(2*n - 1);
    for (int& aa : a) scanf("%d", &aa);
    sort(a.begin(), a.end());

    int ans = -1;
    for (int i = 0; i < n && ans == -1; ++i) {
      const int target = a[a.size() - 1 - i] + a[i];
      int res = Can(target, false);
      if (res != -1) ans = res;
      res = Can(target, true);
      if (res != -1) {
        if (ans != -1) ans = min(ans, res);
        else ans = res;
      }
    }
    if (n > 1) {
      {  // Right
        const int target = a[0] + a[a.size() - 2];
        int res = target - a[a.size() - 1];
        if (res > 0 && Check(target, 0, a.size() - 2))
          ans = res;
      }
      {  // Left
        const int target = a[1] + a[a.size() - 1];
        int res = target - a[0];
        if (res > 0 && Check(target, 1, a.size() - 1)) {
          if (ans != -1) ans = min(ans, res);
          else ans = res;
        }
      }
    }

    printf("Case #%d: %d\n", test_case, ans);
  }
  return 0;
}
