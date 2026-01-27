#include <bits/stdc++.h>

const int kSafeSize = 100;

struct Safe {
  struct Rotation {
    char direction;
    int clicks;
    Rotation(std::istream&& sin) {
      sin >> direction >> clicks;
    }
    Rotation(const std::string& rotation) : Rotation(std::istringstream(rotation)) {}
  };
  std::vector<Rotation> rotations;

  friend std::istream& operator>>(std::istream& sin, Safe& s) {
    s.rotations.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      s.rotations.emplace_back(line);
    }
    return sin;
  }

  int Password() const {
    int curr = 50;
    int ans = 0;
    for (const auto& r : rotations) {
      if (r.direction == 'L') {
        curr -= r.clicks;
      } else {
        curr += r.clicks;
      }
      curr = ((curr % kSafeSize) + kSafeSize) % kSafeSize;

      if (curr == 0) ++ans;
    }
    return ans;
  }
};

int main() {
  Safe safe;
  std::cin >> safe;

  const int ans = safe.Password();
  std::println("Password: {}", ans);

  return 0;
}