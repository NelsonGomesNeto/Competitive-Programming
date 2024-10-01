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
    const lli current_votes = a[candidate];
    const lli total_votes = current_votes + new_votes;
    // Is it possible to distribute `remaining_votes` so that I lose `m -
    // total_above` positions?
    const lli remaining_votes = votes_left - new_votes;
    int first_above =
        std::upper_bound(sorted_a.begin(), sorted_a.end(), total_votes) -
        sorted_a.begin();
    const int total_above = n - first_above;
    const int gap_to_lose = m - total_above;
    DEBUG std::cout << total_votes << " " << first_above << " " << total_above
                    << " " << gap_to_lose << "\n";
    if (gap_to_lose <= 0) return false;

    int current_pos =
        std::lower_bound(sorted_a.begin(), sorted_a.end(), current_votes) -
        sorted_a.begin();
    int lo = first_above - gap_to_lose, hi = first_above - 1;
    const bool should_skip = current_pos >= lo && current_pos <= hi;
    if (should_skip && lo) {
      --lo;
    }
    assert(lo >= 0);
    lli sum_required = gap_to_lose * (total_votes + 1) -
                       (sorted_a_acc[hi + 1] - sorted_a_acc[lo]);
    if (should_skip) {
      sum_required += current_votes;
    }
    DEBUG std::cout << sum_required << " " << remaining_votes << "\n";

    if (first_above == 1 && current_pos == 0) {
      return gap_to_lose > 0;
    }
    // DEBUG {
    //   lli hehe = 0;
    //   bool skipped_self = false;
    //   for (int j = first_above - 1, to_check = gap_to_lose; to_check;
    //        --to_check, --j) {
    //     assert(j >= 0 && j < n);
    //     if (sorted_a[j] == current_votes && !skipped_self) {
    //       ++to_check;
    //       skipped_self = true;
    //       continue;
    //     }
    //     hehe += total_votes - sorted_a[j];
    //     DEBUG std::cout << "\t" << j << " " << sorted_a[j] << " "
    //                     << current_votes << "\n";
    //   }
    //   DEBUG std::cout << "hehe: " << sum_required << " " << hehe << " "
    //                   << remaining_votes << "\n";
    //   if (sum_required != hehe) {
    //     std::cout << candidate << " " << new_votes << "\n";
    //     assert(false);
    //   }
    // }
    return sum_required > remaining_votes;
  }
  lli FindX(const int candidate) {
    if (m == n) return 0;
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