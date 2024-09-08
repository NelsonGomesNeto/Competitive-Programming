#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Spring {
  std::string conditions;
  std::vector<int> dup;

  Spring(const std::string& line) {
    std::istringstream lin(line);
    lin >> conditions;
    for (int d; lin >> d; lin.ignore(1)) dup.push_back(d);
  }

  friend std::ostream& operator<<(std::ostream& stream, const Spring& s) {
    stream << s.conditions << " |";
    for (const int d : s.dup) stream << "," << d;
    stream << "|";
    return stream;
  }

  int Arrangements(int i = 0, int j = -1, int curr = -1) const {
    if (j >= (int)dup.size()) return false;
    if (j >= 0 && j < (int)dup.size() && curr > dup[j]) return false;

    if (i == conditions.size()) {
      return j == dup.size() - 1 && (curr == dup[j] || curr == -1);
    }

    int ans = 0;
    if (conditions[i] == '#') {
      if (curr == -1)
        ans += Arrangements(i + 1, j + 1, 1);
      else
        ans += Arrangements(i + 1, j, curr + 1);
    }
    if (conditions[i] == '.') {
      if (curr != -1 && curr < dup[j]) {
        ans = 0;
      } else {
        ans += Arrangements(i + 1, j, -1);
      }
    }

    if (conditions[i] == '?') {
      if (curr == -1) {
        ans += Arrangements(i + 1, j, -1);
        ans += Arrangements(i + 1, j + 1, 1);
      } else {
        if (curr < dup[j]) {
          ans += Arrangements(i + 1, j, curr + 1);
        } else {
          ans += Arrangements(i + 1, j, -1);
        }
      }
    }

    return ans;
  }

  bool Valid() {
    std::vector<int> blocks;
    for (int i = 0; i < conditions.size(); ++i) {
      if (conditions[i] == '.') continue;

      int j = i;
      while (j + 1 < conditions.size() && conditions[j + 1] == '#') ++j;

      blocks.push_back(j - i + 1);

      i = j;
    }
    return blocks == dup;
  }
  int Brute(int i = 0) {
    if (i == conditions.size()) {
      return Valid();
    }

    int ans = 0;
    if (conditions[i] == '?') {
      conditions[i] = '#';
      ans += Brute(i + 1);
      conditions[i] = '.';
      ans += Brute(i + 1);
      conditions[i] = '?';
    } else {
      ans += Brute(i + 1);
    }

    return ans;
  }
};
std::vector<Spring> springs;

int main() {
  for (std::string line; std::getline(std::cin, line);) {
    springs.push_back(Spring(line));
  }

  int ans = 0;
  for (auto& spring : springs) {
    const int arr = spring.Arrangements();
    DEBUG {
      const int brute = spring.Brute();
      std::cout << spring << " " << arr << " " << brute << std::endl;
      assert(arr == brute);
    }
    ans += arr;
  }
  std::cout << ans << std::endl;
  return 0;
}