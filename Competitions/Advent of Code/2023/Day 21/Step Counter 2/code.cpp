#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
I'll call the input as "base map" and the infinite version of it "infinite map"

### Recognizing patterns
If we walk through the "infinite map" and group by "base map", then we can see
that there are only these kinds of fills:
 1. Center
 2. Adj Center 1
 3. Adj Center 2
 4. Top Left 1
 5. Top Left 2
 6. Top Right 1
 7. Top Right 2
 8. Top 1
 9. Top 2
10. Bottom Left 1
11. Bottom Left 2
12. Bottom Right 1
13. Bottom Right 2
14. Bottom 1
15. Bottom 2
16. Left 1
17. Left 2
18. Right 1
19. Rigth 2
Many of these are not required to always appear, but they can depending on the
number of steps.

So, we can group by that and the number of positions visited with exactly k
steps is:
ans = sum(group_count * visits_in_group)

---
### How does groups cycle?
* How to know exactly which gruops will there be for a given number of steps?
I suspect which groups appear will cycle and only the count will change
Perhaps by getting one image per number of steps will give a clue

Yup, it cycles!
But only after 33 steps and then it cycles every 11 for Left 2
33 Left 2 appears
37 Left 1 -> Adj Center 2 && Left 2 -> Left 1
44 Left 2 appears
48 Left 1 -> Adj Center 1 && Left 2 -> Left 1
55 Left 2 appears
59 Left 1 -> Adj Center 2 && Left 2 -> Left 1
66 Left 2 appears
77 Left 2 appears

Is the start of cycling exactly after 3 * the map size?
  I suspect it's the minimum number of steps for the cycle to start,
  but it may start earlier
And the cycle size always equals the map size?
  YES! \o/
It sounds very reasonable to me.
Let me try a smaller map size.

21 (3 * 7 (map size)) should start the cycle
28 touches the bottom and right borders? YES
35 again? YES YES YES
HERE WE GO

I tested a couple other patterns and that seems to work \o/

---
### How does the count change on every cycle?
The growth is:
* 0 for corners
* 1 per cycle for edges
* rem_cycles^2 per cycle for internal, but there is a BIG CATCH
For internal (adj1 and adj2), we need discover the area by squarerooting
the count. But we need to count the border of them separately because
it's not possible to guarantee that all of them will be filled.

---
### Merge both ideas
Let's benchmark my idea against the 1000 steps on a small map

cycle_size = width
after 5 * cycle_size, it always cycle AFAIK
total_cycles = target_step / cycle_size
rem_steps = target_step % cycle_size
rem_cycles = total_cycles - 5
target_step = (5 + rem_cycles)*cycle_size + rem_steps

So, we find the pattern for `step = 5*cycle_size + rem_steps`
Then ans is:
  extrapolated_group_count = for every group type, we expand according to the
  type and rem_cycles
  ans = sum((group_count + extrapolated_group_count) * visits_in_group)
*/

const int kSteps = 1000;

const int kBlueMask = (1 << 8) - 1;
const int kGreenMask = ((1 << 16) - 1) & ~kBlueMask;
const int kRedMask = ((1 << 24 - 1)) & ~(kGreenMask | kBlueMask);
struct Color {
  int rgb = 0;
  Color() {}
  Color(int c) : rgb(c) {}

  int Red() const { return rgb >> 16; }
  int Green() const { return (rgb & kGreenMask) >> 8; }
  int Blue() const { return rgb & kBlueMask; }
  static Color Random(const int index) {
    static std::vector<Color> kRandomColors{
        Color(0xe6194B), Color(0x3cb44b), Color(0xffe119), Color(0x4363d8),
        Color(0xf58231), Color(0x911eb4), Color(0x42d4f4), Color(0xf032e6),
        Color(0xbfef45), Color(0xfabed4), Color(0x469990), Color(0xdcbeff),
        Color(0x9A6324), Color(0xfffac8), Color(0x800000), Color(0xaaffc3),
        Color(0x808000), Color(0xffd8b1), Color(0x000075), Color(0xa9a9a9)};
    assert(index < kRandomColors.size());
    return kRandomColors[index];
  }
  std::string ToString() {
    std::ostringstream sout;
    sout << Red() << " " << Green() << " " << Blue();
    return sout.str();
  }

  friend std::ostream& operator<<(std::ostream& stream, const Color& c) {
    stream << (char)c.Red() << (char)c.Green() << (char)c.Blue();
    return stream;
  }
};
const Color kBlack = Color(0x000000);
const Color kWhite = Color(0xffffff);
const Color kRed = Color(0xff0000);
const Color kGreen = Color(0x00ff00);
const Color kBlue = Color(0x0000ff);
Color GetColor(const char c) {
  switch (c) {
    case '.':
    case 's':
      return kWhite;
    case '#':
      return kBlack;
    case 'O':
      return kGreen;
    case 'S':
      return kRed;
    default:
      std::cout << "WTF: " << c << "\n";
      std::cout.flush();
      assert(false);
  }
}
const std::vector<std::vector<std::string>> kDigits = {{
                                                           "####",
                                                           "#  #",
                                                           "#  #",
                                                           "#  #",
                                                           "####",
                                                       },
                                                       {
                                                           "   #",
                                                           "   #",
                                                           "   #",
                                                           "   #",
                                                           "   #",
                                                       },
                                                       {
                                                           "####",
                                                           "   #",
                                                           "####",
                                                           "#   ",
                                                           "####",
                                                       },
                                                       {
                                                           "####",
                                                           "   #",
                                                           "####",
                                                           "   #",
                                                           "####",
                                                       },
                                                       {
                                                           "#  #",
                                                           "#  #",
                                                           "####",
                                                           "   #",
                                                           "   #",
                                                       },
                                                       {
                                                           "####",
                                                           "#   ",
                                                           "####",
                                                           "   #",
                                                           "####",
                                                       },
                                                       {
                                                           "####",
                                                           "#   ",
                                                           "####",
                                                           "#  #",
                                                           "####",
                                                       },
                                                       {
                                                           "####",
                                                           "   #",
                                                           "   #",
                                                           "   #",
                                                           "   #",
                                                       },
                                                       {
                                                           "####",
                                                           "#  #",
                                                           "####",
                                                           "#  #",
                                                           "####",
                                                       },
                                                       {
                                                           "####",
                                                           "#  #",
                                                           "####",
                                                           "   #",
                                                           "####",
                                                       }};
void WriteSteps(const int steps, std::vector<std::vector<Color>>& image) {
  int start_pos = image[0].size();
  for (auto& line : image) {
    for (int i = 0; i < 30; ++i) line.push_back(kBlack);
  }

  std::vector<int> digits;
  int num = steps;
  while (num) {
    digits.push_back(num % 10);
    num /= 10;
  }
  if (digits.empty()) digits.push_back(0);
  reverse(digits.begin(), digits.end());

  for (const int d : digits) {
    const auto digit_string = kDigits[d];
    std::vector<std::vector<Color>> digit_image(
        digit_string.size() + 2,
        std::vector<Color>(digit_string[0].size() + 2, kBlue));
    for (int i = 0; i < digit_string.size(); ++i) {
      for (int j = 0; j < digit_string[i].size(); ++j) {
        digit_image[i + 1][j + 1] = digit_string[i][j] == '#' ? kWhite : kBlue;
      }
    }

    for (int i = 0; i < digit_image.size(); ++i) {
      for (int j = 0; j < digit_image[i].size(); ++j) {
        assert(start_pos + j < image[i].size());
        image[i][start_pos + j] = digit_image[i][j];
      }
    }

    start_pos += digit_image.size();
  }
}
void PrintImage(const std::vector<std::vector<Color>>& image) {
  const int n = image.size(), m = image[0].size();
  std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
  ofs << "P6\n" << m << " " << n << "\n255\n";
  for (const auto& line : image)
    for (const auto& color : line) ofs << color;
}

const int di[4] = {0, 1, -1, 0};
const int dj[4] = {1, 0, 0, -1};

struct Pos {
  int i, j;
  Pos() {}
  Pos(const int i, const int j) : i(i), j(j){};

  Pos NextDir(const int d) const { return Pos{i + di[d], j + dj[d]}; }
  bool Parity() const { return ~(i + j) & 1; }
  bool operator<(const Pos& other) const {
    return i < other.i || (i == other.i && j < other.j);
  }
  bool operator==(const Pos& other) const {
    return i == other.i && j == other.j;
  }
  friend std::ostream& operator<<(std::ostream& osout, const Pos& pos) {
    osout << "(" << pos.i << ", " << pos.j << ")";
    return osout;
  }
};

template <>
struct std::hash<Pos> {
  std::size_t operator()(const Pos& p) const noexcept {
    return (((lli)p.i) << 31) + p.j;
  }
};

struct Map {
  Pos start_pos;
  int n, m;
  std::vector<std::string> map;

  int Size() const {
    assert(n == m);
    return n;
  }

  void Build(const std::vector<std::string>& new_map) {
    map = new_map;
    n = map.size(), m = map[0].size();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (map[i][j] == 'S') {
          start_pos = Pos{i, j};
          map[i][j] = '.';
        }
      }
    }
  }

  friend std::istream& operator>>(std::istream& isin, Map& m) {
    std::vector<std::string> map;
    for (std::string line; std::getline(isin, line);) {
      map.push_back(line);
    }
    m.Build(map);
    return isin;
  }
  friend std::ostream& operator<<(std::ostream& osout, const Map& m) {
    for (const std::string& line : m.map) {
      osout << line << "\n";
    }
    return osout;
  }

  int FixBound(const int x, const int upperlimit) const {
    if (x >= upperlimit) return x % upperlimit;
    if (x < 0) return (x % upperlimit + upperlimit) % upperlimit;
    return x;
  }
  bool ValidPos(const Pos p) const {
    return map[FixBound(p.i, n)][FixBound(p.j, m)] == '.';
  }
  std::pair<int, int> GridPos(const Pos& p) const {
    return std::make_pair(p.i / n + (p.i < 0 ? -1 : 0),
                          p.j / m + (p.j < 0 ? -1 : 0));
  }

  // Visits all the positions within max_steps and returns all the positions
  // that were visited.
  std::unordered_set<Pos> Walk(const int max_steps) const {
    std::unordered_set<Pos> visited;

    std::queue<std::pair<Pos, int>> q;
    q.emplace(start_pos, 0);
    while (!q.empty()) {
      const auto [p, steps] = q.front();
      q.pop();

      const auto [it, inserted] = visited.emplace(p);
      if (!inserted) continue;

      if (steps == max_steps) {
        continue;
      }

      for (int d = 0; d < 4; ++d) {
        const Pos np = p.NextDir(d);
        if (!ValidPos(np)) continue;
        q.emplace(np, steps + 1);
      }
    }

    return visited;
  }

  // Returns true iff the position `p` is reachable in exactly `steps`.
  bool VisitableInExactlySteps(const int steps, const Pos& p) const {
    // A position is visited iff, it's position `p` parity is:
    // * equal to the `start_pos` parity, if `max_steps` is even;
    // * not equal to the `start_pos` parity, if the `max_steps` is odd.
    return (~steps & 1) == (start_pos.Parity() == p.Parity());
  }
  // Counts the reachable positions with exactly `max_steps` given the `visited`
  // positions built from the same amount of steps.
  int CountReachable(const int max_steps,
                     const std::unordered_set<Pos>& visited) const {
    int ans = 0;
    for (const Pos& p : visited) {
      ans += VisitableInExactlySteps(max_steps, p);
    }
    return ans;
  }
  int CountReachable(const std::vector<std::string>& visited_block) const {
    int ans = 0;
    for (const std::string& line : visited_block) {
      for (const char c : line) ans += c == 'O' || c == 'S';
    }
    return ans;
  }

  std::tuple<
      std::map<std::vector<std::string>, std::vector<std::pair<int, int>>>,
      std::map<std::pair<int, int>, std::vector<std::string>>,
      std::pair<std::pair<int, int>, std::pair<int, int>>>
  GetGroupCounts(const int max_steps,
                 const std::unordered_set<Pos>& visited) const {
    int loi = 0, hii = 0, loj = 0, hij = 0;
    for (const Pos& p : visited) {
      const auto [gi, gj] = GridPos(p);
      loi = std::min(loi, gi), hii = std::max(hii, gi);
      loj = std::min(loj, gj), hij = std::max(hij, gj);
    }

    std::map<std::vector<std::string>, std::vector<std::pair<int, int>>>
        group_to_block_pos;
    std::map<std::pair<int, int>, std::vector<std::string>> block_pos_to_group;
    for (int gi = loi; gi <= hii; ++gi) {
      for (int gj = loj; gj <= hij; ++gj) {
        std::vector<std::string> block(n, std::string(m, '.'));
        bool has_reachable = false;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            const Pos p{i + gi * n, j + gj * m};
            if (!ValidPos(p)) {
              block[i][j] = '#';
            } else {
              const bool reachable =
                  VisitableInExactlySteps(max_steps, p) && visited.count(p);
              has_reachable |= reachable;
              if (p == start_pos)
                block[i][j] = reachable ? 'S' : 's';
              else
                block[i][j] = reachable ? 'O' : '.';
            }
          }
        }
        if (has_reachable) {
          const bool repeated = group_to_block_pos.count(block);
          group_to_block_pos[block].emplace_back(gi, gj);
        }
        block_pos_to_group[std::make_pair(gi, gj)] = block;
      }
    }
    return std::make_tuple(
        group_to_block_pos, block_pos_to_group,
        std::make_pair(std::make_pair(loi, loj), std::make_pair(hii, hij)));
  }

  // Debug prints the entire walk given the `visited` positions.
  void PrintWalk(const int max_steps,
                 const std::unordered_set<Pos>& visited) const {
    auto [group_to_block_pos, block_pos_to_group, bounding_box] =
        GetGroupCounts(max_steps, visited);
    const auto [loi, loj] = bounding_box.first;
    const auto [hii, hij] = bounding_box.second;
    std::cout << "bounding_box: " << loi << " " << loj << " | " << hii << " "
              << hij << "\n";

    std::ostringstream big_mat_sout;
    std::map<std::vector<std::string>, Color> color_map;
    std::vector<std::vector<Color>> image{{}};
    for (int gi = loi; gi <= hii; ++gi) {
      for (int i = 0; i < n; ++i) {
        for (int gj = loj; gj <= hij; ++gj) {
          const std::pair<int, int> gij(gi, gj);

          int start = 0;
          if (i == 0) {
            std::ostringstream hehe;
            if (group_to_block_pos.count(block_pos_to_group[gij])) hehe << "&";
            hehe << "(" << gi << ", " << gj << ")";
            big_mat_sout << hehe.str();
            start = hehe.str().size();
          }

          for (int j = start; j < m; ++j) {
            big_mat_sout << block_pos_to_group[gij][i][j];
          }
          for (int j = 0; j < m; ++j) {
            Color color = GetColor(block_pos_to_group[gij][i][j]);
            if (block_pos_to_group[gij][i][j] == 'O') {
              auto [it, _] = color_map.try_emplace(
                  block_pos_to_group[gij], Color::Random(color_map.size()));
              color = it->second;
            }
            image.back().push_back(color);
          }
          if (gj != hij) big_mat_sout << "|";
        }
        big_mat_sout << "\n";
        image.push_back(std::vector<Color>{});
      }
      if (gi != hii)
        big_mat_sout << std::string((hij - loj + 1) * (m + 1) - 1, '-') << "\n";
    }
    // PrintImage(image);
    // std::cout << big_mat_sout.str();

    int cnt_by_block = 0;
    for (const auto& [visited_block, repeats] : group_to_block_pos) {
      const int visits = CountReachable(visited_block);
      cnt_by_block += repeats.size() * visits;
      std::cout << "repeats (" << repeats.size() << ") | " << visits << " | "
                << repeats.size() * visits << ":";
      for (const auto& [ri, rj] : repeats)
        std::cout << " (" << ri << ", " << rj << ")";
      std::cout << "\n";
    }
    std::cout << "cnt_by_block: " << cnt_by_block << "\n";
  }

  std::vector<std::vector<Color>> GetWalkImage(
      const int max_steps, const std::unordered_set<Pos>& visited) const {
    auto [group_to_block_pos, block_pos_to_group, bounding_box] =
        GetGroupCounts(max_steps, visited);
    const auto [loi, loj] = bounding_box.first;
    const auto [hii, hij] = bounding_box.second;
    std::cout << "bounding_box: " << loi << " " << loj << " | " << hii << " "
              << hij << "\n";

    std::map<std::vector<std::string>, Color> color_map;
    std::vector<std::vector<Color>> image{{}};
    for (int gi = loi; gi <= hii; ++gi) {
      for (int i = 0; i < n; ++i) {
        for (int gj = loj; gj <= hij; ++gj) {
          const std::pair<int, int> gij(gi, gj);
          for (int j = 0; j < m; ++j) {
            Color color = GetColor(block_pos_to_group[gij][i][j]);
            if (block_pos_to_group[gij][i][j] == 'O') {
              auto [it, _] = color_map.try_emplace(
                  block_pos_to_group[gij], Color::Random(color_map.size()));
              color = it->second;
            }
            image.back().push_back(color);
          }
        }
        image.push_back(std::vector<Color>{});
      }
    }

    WriteSteps(max_steps, image);

    return image;
  }

  bool IsCornerOrCenter(
      const std::pair<std::pair<int, int>, std::pair<int, int>>& bounding_box,
      const std::vector<std::pair<int, int>>& positions) const {
    if (positions.size() == 1) return true;
    const auto [loi, loj] = bounding_box.first;
    const auto [hii, hij] = bounding_box.second;
    for (const auto [i, j] : positions) {
      if ((i == 0 || j == 0) &&
          ((i == loi || i == hii) || (j == loj || j == hij))) {
        return true;
      }
    }
    return false;
  }

  bool IsEdge(const std::vector<std::pair<int, int>>& positions) const {
    assert(positions.size() > 2);
    const int di = positions[1].first - positions[0].first;
    const int dj = positions[1].second - positions[0].second;
    return di == (positions[2].first - positions[1].first) &&
           dj == (positions[2].second - positions[1].second);
  }

  bool IsAdj1(const std::vector<std::pair<int, int>>& positions) const {
    assert(positions.size() > 2);
    for (const auto [i, j] : positions) {
      if (i == 0 && j == 1) return true;
    }
    return false;
  }

  lli GetAdjNewArea(const std::vector<std::pair<int, int>>& positions,
                    const int rem_cycles) const {
    auto diagonal_add = [&](const int i, const int j) {
      const bool i_positive = i > 0;
      const bool j_positive = j > 0;
      if (i_positive ^ j_positive) {
        return i - j;
      } else {
        return i + j;
      }
    };

    std::vector<int> max_by_quadrant(4, 0);
    std::vector<int> diagonal_sum_by_quadrant(4, 0);
    int maximum_distance = 0;
    for (const auto [i, j] : positions) {
      const bool i_positive = i > 0;
      const bool j_positive = j > 0;
      const int quadrant_index = i_positive * 2 + j_positive;
      int& current = max_by_quadrant[quadrant_index];
      const int distance = abs(i) + abs(j);
      if (distance > current) {
        current = distance;
        diagonal_sum_by_quadrant[quadrant_index] = diagonal_add(i, j);
      }
      maximum_distance = std::max(maximum_distance, distance);
    }
    // std::cout << "\t\tmaximum_distance: " << maximum_distance
    //           << " | max_by_quadrant:";
    // for (const int cnt : max_by_quadrant) {
    //   std::cout << " " << cnt;
    // }
    // std::cout << "\n";

    std::vector<int> cnt_by_quadrant(4, 0);
    int cnt_internal = 0;
    for (const auto [i, j] : positions) {
      const bool i_positive = i > 0;
      const bool j_positive = j > 0;
      const int quadrant_index = i_positive * 2 + j_positive;
      if (max_by_quadrant[quadrant_index] == maximum_distance &&
          diagonal_add(i, j) == diagonal_sum_by_quadrant[quadrant_index]) {
        ++cnt_by_quadrant[quadrant_index];
      } else {
        ++cnt_internal;
      }
    }
    // std::cout << "\t\tquadrant:";
    // for (const int cnt : cnt_by_quadrant) {
    //   std::cout << " " << cnt;
    // }
    // std::cout << "\n";
    // std::cout << "\t\tinternal: " << cnt_internal << "\n";

    const lli side = round(sqrt(cnt_internal));
    const lli new_side = side + rem_cycles;
    const lli new_area = new_side * new_side;
    lli total = new_area;
    for (const int cnt : cnt_by_quadrant) {
      if (cnt == 0) continue;
      total += cnt + rem_cycles;
    }
    // std::cout << "\t\tside: " << side << " | new_side: " << new_side
    //           << " | new_area: " << new_area << "\n";

    // std::cout << "\t\ttotal: " << total << "\n";

    return total;
  }

  lli Solve(const int max_steps) const {
    const int cycle_size = Size();
    const int total_cycles = max_steps / cycle_size;
    const int rem_steps = max_steps % cycle_size;
    // To avoid flipping which internal (Adj1, Adj2) is on the border, I want
    // the `rem_cycles` to always be even.
    const int initial_cycles = total_cycles & 1 ? 5 : 6;
    const int cycle_start = cycle_size * initial_cycles;
    const int rem_cycles = total_cycles - initial_cycles;

    std::cout << "max_steps: " << max_steps << "\n";
    std::cout << "cycle_size: " << cycle_size << "\n";
    std::cout << "initial_cycles: " << initial_cycles << "\n";
    std::cout << "cycle_start: " << cycle_start << "\n";
    std::cout << "rem_cycles: " << rem_cycles << "\n";
    std::cout << "rem_steps: " << rem_steps << "\n";
    std::cout << "cycle_start + cycle_size*rem_cycles + rem_steps: "
              << cycle_start + cycle_size * rem_cycles + rem_steps << "\n";

    const std::unordered_set<Pos> visited = Walk(cycle_start + rem_steps);
    PrintWalk(cycle_start + rem_steps, visited);

    auto [group_to_block_pos, block_pos_to_group, bounding_box] =
        GetGroupCounts(max_steps, visited);
    const auto [loi, loj] = bounding_box.first;
    const auto [hii, hij] = bounding_box.second;
    std::cout << "bounding_box: " << loi << " " << loj << " | " << hii << " "
              << hij << "\n";

    lli ans = 0;
    for (const auto& [block, block_positions] : group_to_block_pos) {
      /* The growth is:
        * 0 for corners
        * 1 per cycle for edges
        * rem_cycles^2 per cycle for internal, but there is a BIG CATCH
        For internal (adj1 and adj2), we need discover the area by squarerooting
        the count. But we need to count the border of them separately because
        it's not possible to guarantee that all of them will be filled.
      */
      const lli visits_in_group = CountReachable(block);
      const auto [group_count, type] = [&]() -> std::pair<lli, std::string> {
        if (IsCornerOrCenter(bounding_box, block_positions)) {
          return std::make_pair(block_positions.size(), "corner");
        } else if (IsEdge(block_positions)) {
          return std::make_pair(block_positions.size() + rem_cycles, "edge  ");
        } else {
          if (IsAdj1(block_positions)) {
            const lli new_area = GetAdjNewArea(block_positions, rem_cycles);
            std::cout << "new_area: " << new_area << "\n";
            return std::make_pair(new_area, "adj1  ");
          } else {  // Adj2
            // Adj2 area is always - 1 because center is part of adj2.
            const lli new_area = GetAdjNewArea(block_positions, rem_cycles) - 1;
            std::cout << "new_area: " << new_area << "\n";
            return std::make_pair(new_area, "adj2  ");
          }
        }
      }();
      const lli to_add = group_count * visits_in_group;
      ans += to_add;
      if (type != "edge  " && type != "corner")
        std::cout << type
                  << " | block_positions.size(): " << block_positions.size()
                  << " | group_count: " << group_count
                  << " | visits_in_group: " << visits_in_group << " = "
                  << to_add << "\n";
    }
    // ans = sum(group_count * visits_in_group);
    return ans;
  }
};

void AnalyzeImages(Map& map) {
  std::vector<std::vector<std::vector<Color>>> images;
  for (int i = 0; i <= 77; ++i) {
    const std::unordered_set<Pos> visited = map.Walk(i);
    images.push_back(map.GetWalkImage(i, visited));
  }

  std::vector<std::vector<Color>> big_image;
  for (auto& image : images) {
    for (auto& line : image) {
      while (line.size() < images.back()[0].size()) line.push_back(kBlack);
      big_image.push_back(line);
    }
  }
  PrintImage(big_image);
}

Map map;

int main() {
  std::cin >> map;

  // AnalyzeImages(map);

  // map.PrintWalk(kSteps, map.Walk(kSteps));
  // std::cout << "---------------------------\n";

  const lli ans = map.Solve(kSteps);
  std::cout << "ans: " << ans << "\n";

  return 0;
}
