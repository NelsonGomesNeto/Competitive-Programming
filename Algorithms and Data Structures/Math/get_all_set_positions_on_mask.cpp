#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  const int mask = 0b10100;

  std::vector<int> positions;
  for (uint32_t curr_mask = mask; curr_mask != 0; curr_mask &= curr_mask - 1) {
    const int i = std::countr_zero(curr_mask);
    positions.push_back(i);
  }
  std::println("{}", positions);

  return 0;
}
