#include <bits/stdc++.h>

const int kIterations = 50;

std::string LookAndSay(const std::string& si, const int iterations,
                       const bool verbose = false) {
  std::string curr = si;
  for (int it = 0; it < iterations; ++it) {
    if (verbose) std::println("{}: {}", it, curr);
    std::string next;
    next.reserve(curr.size());
    for (int i = 0; i < (int)curr.size(); ++i) {
      int j = i;
      while (j + 1 < (int)curr.size() && curr[j + 1] == curr[i]) ++j;
      const int cnt = j - i + 1;
      next.push_back('0' + cnt);
      next.push_back(curr[i]);
      i = j;
    }
    curr = next;
  }
  if (verbose) std::println("{}: {}", iterations, curr);
  return curr;
}

int main() {
  std::string initial_state;
  std::cin >> initial_state;

  std::println("initial_state: {}", initial_state);

  const std::string ans =
      LookAndSay(initial_state, /*iterations=*/kIterations, /*verbose=*/true);
  std::println("ans: {}", ans.size());

  return 0;
}
