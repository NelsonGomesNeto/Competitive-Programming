#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  lli k, votes_left;
  std::vector<lli> a;
  std::vector<lli> sorted_a;
  std::vector<lli> ans;
  std::vector<lli> sorted_a_acc;

  bool Elected(const int candidate, const lli new_votes) {
    const lli total_votes = a[candidate] + new_votes;
    std::vector<lli> hehe = a;
    hehe[candidate] = total_votes;
    std::sort(hehe.begin(), hehe.end());

    int first_below = std::upper_bound(hehe.begin(), hehe.end(), total_votes) -
                      hehe.begin() - 2;
    lli remaining_votes = votes_left - new_votes;
    for (; remaining_votes && first_below >= 0; --first_below) {
      lli curr = hehe[first_below];
      lli delta = total_votes + 1 - curr;
      if (delta <= remaining_votes) {
        hehe[first_below] += delta;
        remaining_votes -= delta;
      }
    }

    std::sort(hehe.begin(), hehe.end());

    int first_above =
        std::upper_bound(hehe.begin(), hehe.end(), total_votes) - hehe.begin();
    const int total_above = n - first_above;
    return total_above < m;
  }
  lli FindX(const int candidate) {
    // if (n == 1) return 0;
    lli lo = 0, hi = votes_left;
    DEBUG lo = 0, hi = 0;
    while (lo < hi) {
      lli mid = (lo + hi) >> 1;
      if (Elected(candidate, mid))
        hi = mid;
      else
        lo = mid + 1;
    }
    if (Elected(candidate, lo))
      return lo;
    else
      return -1;
  }

  bool Solve() {
    if (!(std::cin >> n >> m >> k)) return false;

    votes_left = k;
    a.resize(n);
    for (lli& aa : a) {
      std::cin >> aa;
      votes_left -= aa;
    }

    sorted_a = a;
    std::sort(sorted_a.begin(), sorted_a.end());
    sorted_a_acc.resize(n + 1, 0);
    for (int i = 0; i < n; ++i) {
      sorted_a_acc[i + 1] = sorted_a_acc[i] + sorted_a[i];
    }

    DEBUG {
      std::cout << "sorted_a: ";
      for (int i = 0; i < n; ++i) {
        if (i) std::cout << " ";
        std::cout << sorted_a[i];
      }
      std::cout << "\n";
    }

    ans.resize(n, -1);
    DEBUG ans[0] = FindX(0);
    else {
      for (int i = 0; i < n; ++i) {
        ans[i] = FindX(i);
      }
    }

    for (int i = 0; i < n; ++i) {
      if (i) std::cout << " ";
      std::cout << ans[i];
    }
    std::cout << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}