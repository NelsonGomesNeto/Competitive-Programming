#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kFreeSpace = -1;

struct Problem {
  std::string disk_map;
  std::vector<int> disk, compacted_disk;

  std::string DiskToString(const std::vector<int>& a) {
    std::ostringstream sout;
    int line_breaks = 0;
    for (const int cel : a) {
      if (cel == kFreeSpace)
        sout << '.';
      else
        sout << cel;

      if (((int)sout.str().size() - line_breaks) % 80 == 0) {
        sout << '\n';
        ++line_breaks;
      }
    }
    return sout.str();
  }

  int CharToInt(const char id) { return id - '0'; }

  void CompactDisk() {
    compacted_disk = disk;
    for (int i = 0, j = compacted_disk.size() - 1; i < j;) {
      while (i < j && compacted_disk[i] != kFreeSpace) ++i;
      while (i < j && compacted_disk[j] == kFreeSpace) --j;
      std::swap(compacted_disk[i++], compacted_disk[j--]);
    }
  }

  void Solve() {
    std::cin >> disk_map;

    for (int i = 0, id = 0; i < disk_map.size(); ++i) {
      const int size = CharToInt(disk_map[i]);
      if (i & 1) {
        for (int j = 0; j < size; ++j) disk.push_back(kFreeSpace);
      } else {
        for (int j = 0; j < size; ++j) disk.push_back(id);
        ++id;
      }
    }
    CompactDisk();

    DEBUG {
      std::cout << disk_map << "\n";
      std::cout << DiskToString(disk) << "\n";
      std::cout << DiskToString(compacted_disk) << "\n";
    }

    lli ans = 0;
    for (int i = 0; i < compacted_disk.size(); ++i) {
      if (compacted_disk[i] == kFreeSpace) continue;
      const int id = compacted_disk[i];
      ans += (lli)i * id;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
