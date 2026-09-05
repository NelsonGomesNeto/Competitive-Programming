#include <bits/stdc++.h>

const int kMaxHouse = 1e7;

struct Elves {
  const std::array<int, kMaxHouse + 1> houses;
  Elves()
      : houses([&]() {
          std::array<int, kMaxHouse + 1> hs;
          std::ranges::fill(hs, 0);
          for (int i = 1; i <= kMaxHouse; ++i) {
            for (int j = i; j <= kMaxHouse; j += i) {
              assert(j >= 0 && j <= kMaxHouse);
              hs[j] += i * 10;
            }
          }
          return hs;
        }()) {}

  int FirstHouse(const int target) const {
    int biggest_log10 = -1;
    for (const auto [house, presents] : houses | std::views::enumerate) {
      if (const int log10 = std::floor(std::log10(house));
          log10 > biggest_log10 ||
          (log10 >= 0 && house % (int)std::pow(10, log10) == 0)) {
        biggest_log10 = log10;
        std::println("\tHouse {} got {} presents", house, presents);
      }
      if (presents >= target) {
        return house;
      }
    }
    assert(false);
  }
};

int main() {
  int target;
  std::cin >> target;

  std::println("target: {}", target);

  const Elves elves;
  const int ans = elves.FirstHouse(target);
  std::println("ans: {}", ans);

  return 0;
}
