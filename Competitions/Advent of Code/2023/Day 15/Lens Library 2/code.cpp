#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct HashMap {
  std::vector<std::vector<std::pair<std::string, int>>> boxes;
  HashMap() : boxes(256) {}

  int Hash(const std::string& s) {
    int ans = 0;
    for (int c : s) {
      ans += c;
      ans *= 17;
      ans %= 256;
    }
    return ans;
  }

  void Read(const std::string& s) {
    std::string k;

    bool equal_op;
    for (char c : s) {
      if (c == '=' || c == '-') {
        equal_op = c == '=';
        break;
      }
      k.push_back(c);
    }

    auto& box = boxes[Hash(k)];
    if (equal_op) {
      int v;
      std::istringstream sin(s.substr(k.size() + 1));
      sin >> v;

      bool added = false;
      for (auto it = box.begin(); it != box.end(); ++it) {
        if (it->first == k) {
          it->second = v;
          added = true;
          break;
        }
      }
      if (!added) box.emplace_back(k, v);
    } else {
      auto it = std::find_if(box.begin(), box.end(),
                             [&k](const auto& kv) { return kv.first == k; });
      if (it != box.end()) box.erase(it);
    }
  }

  int Power() {
    int ans = 0;
    for (int i = 0; i < boxes.size(); ++i) {
      for (int j = 0; j < boxes[i].size(); ++j) {
        std::cout << "Box " << i << ", slot " << j
                  << ", value: " << boxes[i][j].first << "="
                  << boxes[i][j].second << std::endl;
        ans += (i + 1) * (j + 1) * boxes[i][j].second;
      }
    }
    return ans;
  }
};
HashMap hash_map;
std::vector<std::string> sequences;

int main() {
  for (std::string s; std::getline(std::cin, s, ',');) {
    sequences.push_back(s);
  }

  for (const auto& s : sequences) {
    hash_map.Read(s);
  }
  int ans = hash_map.Power();
  std::cout << ans << std::endl;
  return 0;
}
