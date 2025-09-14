#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int main() {
  std::string s;
  std::cin >> s;
  std::map<std::string, std::string> dict{
      {"red", "SSS"}, {"blue", "FFF"}, {"green", "MMM"}};
  const auto it = dict.find(s);
  if (it == dict.end()) {
    std::cout << "Unknown\n";
  } else {
    std::cout << it->second << "\n";
  }
  return 0;
}