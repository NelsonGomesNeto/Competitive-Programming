#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  //                     9876543210
  const uint32_t mask = 0b100110100;

  std::vector<int> positions;
  // I suppose this is faster, but the one below is a lot easier to remember
  // hahahah.
  // for (uint32_t curr_mask = mask; curr_mask != 0; curr_mask &= curr_mask - 1)
  // {
  //   const int i = std::countr_zero(curr_mask);
  //   positions.push_back(i);
  // }
  for (int i = std::countr_zero(mask), todo = std::popcount(mask); todo > 0;
       --todo, i += std::countr_zero(mask >> (i + 1)) + 1) {
    std::println("{} {:b} {}", i, mask >> (i + 1),
                 i + std::countr_zero(mask >> (i + 1)) + 1);
    positions.push_back(i);
  }
  std::println("{}", positions);

  return 0;
}
