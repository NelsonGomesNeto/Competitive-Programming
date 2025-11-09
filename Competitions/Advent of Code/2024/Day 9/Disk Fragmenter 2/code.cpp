#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

const int kFreeSpace = -1;

struct Problem {
  std::string disk_map;

  struct File {
    int id;
    int size;
    bool IsFreeSpace() const { return id == kFreeSpace; }
  };
  std::vector<File> disk;
  std::list<File> compacted_disk;

  template <class Iterable>
  std::string DiskToString(const Iterable& a) {
    std::ostringstream sout;
    int line_breaks = 0;
    for (const auto& file : a) {
      if (!sout.str().empty()) sout << " ";
      if (file.IsFreeSpace())
        sout << "." << file.size;
      else
        sout << "(" << file.id << ", " << file.size << ")";

      if (((int)sout.str().size() - line_breaks) % 80 == 0) {
        sout << '\n';
        ++line_breaks;
      }
    }
    return sout.str();
  }

  int CharToInt(const char id) { return id - '0'; }

  void CompactDisk() {
    compacted_disk = std::list<File>(disk.begin(), disk.end());
    for (auto jt = std::prev(compacted_disk.end()); jt != compacted_disk.end();
         --jt) {
      while (jt != compacted_disk.end() && jt->IsFreeSpace()) --jt;
      const File& to_move = *jt;

      auto it = compacted_disk.begin();
      while (it != jt && (!it->IsFreeSpace() || it->size < to_move.size)) ++it;

      if (it == jt) continue;

      it->size -= to_move.size;
      if (it->size == 0) it = compacted_disk.erase(it);

      compacted_disk.insert(it, to_move);

      jt->id = kFreeSpace;
      auto MergeFreeSpace = [&](auto cit) {
        if (cit == compacted_disk.end() || !cit->IsFreeSpace()) return;
        jt->size += cit->size;
        compacted_disk.erase(cit);
      };
      MergeFreeSpace(std::next(jt));
      MergeFreeSpace(std::prev(jt));
    }
  }

  void Solve() {
    std::cin >> disk_map;

    for (int i = 0, id = 0; i < disk_map.size(); ++i) {
      const int size = CharToInt(disk_map[i]);
      if (i & 1) {
        disk.emplace_back(kFreeSpace, size);
      } else {
        disk.emplace_back(id, size);
        ++id;
      }
    }
    CompactDisk();

    DEBUG {
      std::cout << disk_map << "\n";
      std::cout << "disk: " << DiskToString(disk) << "\n";
      std::cout << "-------------\n";
      std::cout << "comp: " << DiskToString(compacted_disk) << "\n";
    }

    lli ans = 0, i = 0;
    for (const File& f : compacted_disk) {
      if (!f.IsFreeSpace()) {
        for (int j = 0; j < f.size; ++j) ans += (lli)(i + j) * f.id;
      }
      i += f.size;
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
