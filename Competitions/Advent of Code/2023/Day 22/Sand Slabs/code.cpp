#include <bits/stdc++.h>
#define DEBUG if (1)
#define lli long long int
#define ldouble long double

enum Coordinate { X, Y, Z };
struct Pos {
  int x, y, z;

  Pos(const int x, const int y, const int z) : x(x), y(y), z(z) {}
  Pos(const std::string& pos) {
    std::istringstream sin(pos);
    char ignore;
    sin >> x >> ignore >> y >> ignore >> z;
    // std::sscanf(pos.data(), "%d,%d,%d", &x, &y, &z);
  }
  friend std::ostream& operator<<(std::ostream& sout, const Pos& p) {
    sout << "(" << std::setfill(' ') << std::setw(2) << p.x << ","
         << std::setfill(' ') << std::setw(2) << p.y << "," << std::setfill(' ')
         << std::setw(2) << p.z << ")";
    return sout;
  }

  Pos operator-(const Pos& other) const {
    return Pos{x - other.x, y - other.y, z - other.z};
  }
  bool operator<(const Pos& other) const {
    return x < other.x || (x == other.x && y < other.y) ||
           (x == other.x && y == other.y && z < other.z);
  }

  int Get(const Coordinate coordinate) const {
    switch (coordinate) {
      case Coordinate::X:
        return x;
      case Coordinate::Y:
        return y;
      case Coordinate::Z:
      default:
        return z;
    }
  }

  void ApplyDelta(const int delta, const Coordinate coordinate) {
    switch (coordinate) {
      case Coordinate::X:
        x += delta;
        return;
      case Coordinate::Y:
        y += delta;
        return;
      case Coordinate::Z:
      default:
        z += delta;
        return;
    }
  }
};

struct Brick {
  std::vector<Pos> corners;

  friend std::istream& operator>>(std::istream& isin, Brick& b) {
    std::string line;
    std::getline(isin, line);
    std::istringstream sin(line);
    std::vector<Pos> corners;
    for (std::string corner; std::getline(sin, corner, '~');) {
      corners.emplace_back(corner);
    }
    if (!corners.empty()) {
      assert(corners.size() == 2);
      b = Brick{corners};
    }
    return isin;
  }
  friend std::ostream& operator<<(std::ostream& sout, const Brick& b) {
    for (const Pos& pos : b.corners) {
      sout << pos << " | ";
    }
    const Pos delta = b.corners[1] - b.corners[0];
    sout << "delta: " << delta;
    if ((delta.x != 0) + (delta.y != 0) + (delta.z != 0) > 1) {
      sout << " BIG";
    }
    return sout;
  }

  std::pair<int, int> GetMinMax(const Coordinate coordinate) const {
    return std::make_pair(
        std::min(corners[0].Get(coordinate), corners[1].Get(coordinate)),
        std::max(corners[0].Get(coordinate), corners[1].Get(coordinate)));
  }

  void ApplyDelta(const int delta, const Coordinate coordinate) {
    corners[0].ApplyDelta(delta, coordinate);
  }
};

void InternalSortAndMakeUnique(std::vector<std::vector<int>>& arr) {
  for (std::vector<int>& a : arr) {
    sort(a.begin(), a.end());
    a.resize(std::distance(a.begin(), std::unique(a.begin(), a.end())));
  }
}

char GetName(const int i) { return 'A' + (i % 26); }
int GetLastDigit(const int i) { return i % 10; }

struct Snapshot {
  std::vector<Brick> bricks;
  std::map<Pos, int> pos_to_brick;
  // belows_dag[u] = {v, w} means u is on top of v an w
  // aboves_dag[u] = {v, w} means u is below v and w
  std::vector<std::vector<int>> belows_dag, aboves_dag;

  Snapshot() {}
  Snapshot(const std::vector<Brick>& bricks_) : bricks(bricks_) {
    for (int i = 0; i < bricks.size(); ++i) {
      const Brick& b = bricks[i];
      const auto [lox, hix] = b.GetMinMax(Coordinate::X);
      const auto [loy, hiy] = b.GetMinMax(Coordinate::Y);
      const auto [loz, hiz] = b.GetMinMax(Coordinate::Z);
      for (int x = lox; x <= hix; ++x) {
        for (int y = loy; y <= hiy; ++y) {
          for (int z = loz; z <= hiz; ++z) {
            pos_to_brick[Pos{x, y, z}] = i;
          }
        }
      }
    }

    BuildDags();
  }

  void BuildDags() {
    belows_dag.clear();
    belows_dag.resize(bricks.size());
    aboves_dag.clear();
    aboves_dag.resize(bricks.size());
    for (int i = 0; i < bricks.size(); ++i) {
      const Brick& b = bricks[i];
      const auto [lox, hix] = b.GetMinMax(Coordinate::X);
      const auto [loy, hiy] = b.GetMinMax(Coordinate::Y);
      const int loz = b.GetMinMax(Coordinate::Z).first;
      if (loz == 1) continue;
      for (int x = lox; x <= hix; ++x) {
        for (int y = loy; y <= hiy; ++y) {
          const Pos below{x, y, loz - 1};
          auto below_it = pos_to_brick.find(below);
          if (below_it == pos_to_brick.end()) continue;
          belows_dag[i].push_back(below_it->second);
          aboves_dag[below_it->second].push_back(i);
        }
      }
    }
    InternalSortAndMakeUnique(belows_dag);
    InternalSortAndMakeUnique(aboves_dag);
  }

  friend std::istream& operator>>(std::istream& isin, Snapshot& s) {
    std::vector<Brick> bricks;
    Brick brick;
    while (isin >> brick) {
      bricks.push_back(brick);
    }
    s = Snapshot(bricks);
    return isin;
  }
  friend std::ostream& operator<<(std::ostream& sout, const Snapshot& s) {
    sout << "Bricks (" << s.bricks.size() << ")\n";
    for (int i = 0; i < s.bricks.size(); ++i) {
      const Brick& b = s.bricks[i];
      sout << GetName(i) << ": " << b << "\n";
      sout << "\tbelow:";
      for (const int below : s.belows_dag[i]) {
        sout << " " << GetName(below);
      }
      sout << "\n";
      sout << "\tabove:";
      for (const int above : s.aboves_dag[i]) {
        sout << " " << GetName(above);
      }
      sout << "\n";
    }
    return sout;
  }

  std::pair<int, int> GetMinMax(const Coordinate coordinate) const {
    int lo = std::numeric_limits<int>::max(),
        hi = std::numeric_limits<int>::min();
    for (const Brick& b : bricks) {
      const auto [blo, bhi] = b.GetMinMax(coordinate);
      lo = std::min(lo, blo);
      hi = std::max(hi, bhi);
    }
    return std::make_pair(lo, hi);
  }

  void Fall() {
    std::cout << "Falling!\n";

    std::vector<std::pair<int, int>> z_bricks;
    for (int i = 0; i < bricks.size(); ++i) {
      const int loz = bricks[i].GetMinMax(Coordinate::Z).first;
      z_bricks.emplace_back(loz, i);
    }
    sort(z_bricks.begin(), z_bricks.end());

    pos_to_brick.clear();
    for (const auto [_, i] : z_bricks) {
      Brick& b = bricks[i];
      const auto [lox, hix] = b.GetMinMax(Coordinate::X);
      const auto [loy, hiy] = b.GetMinMax(Coordinate::Y);
      auto [loz, hiz] = b.GetMinMax(Coordinate::Z);
      int z = loz;

      auto can_fall = [&](const int next_z) -> bool {
        if (next_z == 0) return false;
        for (int x = lox; x <= hix; ++x) {
          for (int y = loy; y <= hiy; ++y) {
            Pos pos{x, y, next_z};
            if (pos_to_brick.count(pos)) return false;
          }
        }
        return true;
      };

      while (can_fall(z - 1)) --z;

      const int delta_z = loz - z;
      b.ApplyDelta(-delta_z, Coordinate::Z);
      loz -= delta_z, hiz -= delta_z;

      for (int x = lox; x <= hix; ++x) {
        for (int y = loy; y <= hiy; ++y) {
          for (int z = loz; z <= hiz; ++z) {
            pos_to_brick[Pos{x, y, z}] = i;
          }
        }
      }
    }

    BuildDags();
  }

  int Solve() const {
    int ans = 0;
    for (int i = 0; i < aboves_dag.size(); ++i) {
      const std::vector<int>& aboves = aboves_dag[i];
      bool all_above_has_at_least_two_dep = true;
      for (const int above : aboves) {
        if (belows_dag[above].size() >= 2) continue;
        all_above_has_at_least_two_dep = false;
      }
      DEBUG if (all_above_has_at_least_two_dep) {
        std::cout << "Safe: " << GetName(i) << "\n";
      }
      ans += all_above_has_at_least_two_dep;
    }
    return ans;
  }

  void PrintPlanes() const {
    std::ostringstream sout;

    const auto [lox, hix] = GetMinMax(Coordinate::X);
    const int midx = (lox + hix) >> 1;
    const auto [loy, hiy] = GetMinMax(Coordinate::Y);
    const int midy = (loy + hiy) >> 1;
    const auto [loz, hiz] = GetMinMax(Coordinate::Z);
    const int midz = (loz + hiz) >> 1;
    sout << "x = [" << lox << " : " << hix << "]\n";
    sout << "y = [" << loy << " : " << hiy << "]\n";
    sout << "z = [" << loz << " : " << hiz << "]\n";
    for (int y = loy; y <= hiy; ++y) {
      sout << "xz plane y = " << y << "\n";
      sout << std::string(midx - lox, ' ') << 'x'
           << std::string(hix - midx, ' ') << "\n";
      for (int x = lox; x <= hix; ++x) {
        sout << GetLastDigit(x);
      }
      sout << "\n";
      for (int z = hiz; z >= loz; --z) {
        for (int x = lox; x <= hix; ++x) {
          const Pos p{x, y, z};
          auto brick_it = pos_to_brick.find(p);
          if (brick_it == pos_to_brick.end()) {
            sout << ".";
          } else {
            sout << GetName(brick_it->second);
          }
        }
        sout << " " << GetLastDigit(z);
        if (z == midz) sout << " z";
        sout << "\n";
      }
      sout << std::string(hix - lox + 1, '-') << " 0\n";
    }
    std::cout << sout.str();
  }
};
Snapshot snapshot;

int main() {
  std::cin >> snapshot;

  DEBUG {
    std::cout << snapshot;
    snapshot.PrintPlanes();
    std::cout << "\n" << std::string(80, '-') << "\n\n";

    snapshot.Fall();
    std::cout << "\n" << std::string(80, '-') << "\n\n";

    std::cout << snapshot;
    snapshot.PrintPlanes();
    std::cout << "\n" << std::string(80, '-') << "\n\n";
  }
  else {
    snapshot.Fall();
  }

  int ans = snapshot.Solve();
  std::cout << "ans: " << ans << "\n";

  return 0;
}
