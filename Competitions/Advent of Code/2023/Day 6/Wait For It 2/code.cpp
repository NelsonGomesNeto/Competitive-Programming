#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int Digits(lli x) {
  int digits = x == 0;
  while (x) {
    x /= 10, ++digits;
  }
  return digits;
}
lli Pow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans *= x;
    x *= x, y >>= 1LL;
  }
  return ans;
}

std::vector<lli> times, distance;
std::vector<lli> ReadArray() {
  std::vector<lli> a;
  std::string line;
  std::getline(std::cin, line);

  std::istringstream si(line);
  si.ignore(std::numeric_limits<int>::max(), ':');

  lli total = 0, aa;
  while (si >> aa) {
    total = total*Pow(10, Digits(aa)) + aa;
  }
  a.push_back(total);

  return a;
}

void PrintArray(const std::vector<lli>& a) {
  for (lli aa : a) {
    std::cout << " " << aa;
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  times = ReadArray();
  distance = ReadArray();

  DEBUG {
    PrintArray(times);
    PrintArray(distance);
  }

  lli ans = 1;
  for (int i = 0; i < times.size(); ++i) {
    const lli t = times[i], d = distance[i];
    DEBUG std::cout << t << " " << d << std::endl;

    lli possible = 0;
    for (lli wait = 0; wait < t; ++wait) {
      const lli rem = t - wait;
      const lli dist = rem * wait;
      possible += dist > d;
    }

    ans *= possible;
  }
  std::cout << ans << std::endl;

  return 0;
}
