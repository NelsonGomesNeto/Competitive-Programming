#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::vector<int> times, distance;
std::vector<int> ReadArray() {
  std::vector<int> a;
  std::string line;
  std::getline(std::cin, line);

  std::istringstream si(line);
  si.ignore(std::numeric_limits<int>::max(), ':');

  int aa;
  while (si >> aa) {
    a.push_back(aa);
  }

  return a;
}

void PrintArray(const std::vector<int>& a) {
  for (int aa : a) {
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
    const int t = times[i], d = distance[i];
    DEBUG std::cout << t << " " << d << std::endl;

    lli possible = 0;
    for (int wait = 0; wait < t; ++wait) {
      const int rem = t - wait;
      const int dist = rem * wait;
      possible += dist > d;
    }

    ans *= possible;
  }
  std::cout << ans << std::endl;

  return 0;
}
