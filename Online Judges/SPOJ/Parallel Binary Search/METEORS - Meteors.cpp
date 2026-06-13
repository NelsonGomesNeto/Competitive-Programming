#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
### Problem:
n `states`, m `sectors`.
  Each `state` owns some `sectors`.
`k` `showers`.
  Each `shower` at time `t` will add `x` meteors to range [l : r]
  (or [0 : r] + [l : -1]).
For each `state`, find the first `t` after which it will have collected `y`
meteors.

### Idea:
Simulating the showers is O(n*lg(n)).
Suppose we had a single state.
Then, we can do a binary search for the answer and simulate.
The simulation is the same for all states. So, WHAT IF did all binary searches
at once?
I mean, maitain the search params for each binary search and when simulating:
update the params accordingly.
It may look as if it would become O(n^2*lg(n)) but it's actually O(n*lg(n)^2)
because you'll do at most lg(n) simulations and each simulation is just
O(n*lg(n)).

### Problem downside :(
FYI This problem requires you to hyper optimize.
So, I couldn't make it pass with a Recursive Segmentree. I had to resort to an
Iterative Segmentree with the "prefix sum" trick for range updates without lazy
propagation.
*/

struct Data {
  lli value;
  Data Merge(const Data& other) const { return Data{value + other.value}; }
};
// DON'T FORGET TO DEFINE THE NIL!!!
const Data kNil = Data{0};

template <class T>
struct IterativeSegmentTree {
  int size;
  std::vector<T> data;
  std::vector<T> st;
  T nil;
  IterativeSegmentTree() : IterativeSegmentTree(/*size=*/0, nil) {}
  IterativeSegmentTree(const int size_, const T nil_) : size(size_), nil(nil_) {
    data.resize(size, nil);
    st.resize(4 * size);
  }
  IterativeSegmentTree(const std::vector<T>& data_, const T nil_)
      : size(data_.size()), data(data_), nil(nil_) {
    st.resize(4 * size);
    Build();
  }
  void Build() {
    for (int i = 0; i < size; i++) st[size + i] = data[i];
    for (int i = size - 1; i; i--) st[i] = st[2 * i].Merge(st[2 * i + 1]);
  }
  T Query(int lo, int hi) {
    T ans = nil;
    for (lo += size, hi += size + 1; lo < hi; lo >>= 1, hi >>= 1) {
      if (lo & 1) ans = ans.Merge(st[lo++]);
      if (hi & 1) ans = ans.Merge(st[--hi]);
    }
    return ans;
  }
  void Update(const int pos, const T& value) {
    data[pos].value += value.value;
    st[pos + size] = data[pos];
    for (int i = (pos + size) >> 1; i; i >>= 1)
      st[i] = st[2 * i].Merge(st[2 * i + 1]);
  }
};

struct TestCase {
  int states_count, sectors_count;
  std::vector<int> state_by_sector;
  std::vector<int> samples_by_state;
  std::vector<std::vector<int>> sectors_by_state;
  int showers_count;
  struct Shower {
    int l, r, meteors;
  };
  std::vector<Shower> showers;

  std::vector<int> ans_by_state;
  struct BinarySearchParams {
    int lo, hi;
  };
  std::vector<BinarySearchParams> search_by_state;
  std::vector<std::vector<int>> states_by_time;
  IterativeSegmentTree<Data> segtree;
  void SimulateShowers() {
    // For faster queries, we do the "in-out"/"prefix sum" trick to perform
    // range updates (but point queries) on a regular SegmentTree \o/.
    const auto PointQuery = [&](const int pos) {
      return segtree.Query(0, pos).value;
    };
    const auto RangeUpdate = [&](const int lo, const int hi,
                                 const int meteors) {
      segtree.Update(lo, Data{meteors}), segtree.Update(hi + 1, Data{-meteors});
    };

    // O(max(|showers|, |sectors|, |states|)). In the worst case, we'll run
    // through all showers, sectors and states.
    for (int i = 0; i < showers_count; ++i) {
      const int t = i + 1;
      const auto [l, r, meteors] = showers[i];
      // O(lg(|sectors|))
      if (l > r) {
        RangeUpdate(0, r, meteors), RangeUpdate(l, sectors_count - 1, meteors);
      } else {
        RangeUpdate(l, r, meteors);
      }

      // O(1) because we'll only process a `state` ONCE simulation (when we're
      // guessing `t` for that `state`).
      for (const auto state : states_by_time[t]) {
        auto& [lo, hi] = search_by_state[state];
        lli sum = 0;
        for (const int sector : sectors_by_state[state]) {
          sum += PointQuery(sector);
          if (sum >= samples_by_state[state]) break;
        }
        if (sum >= samples_by_state[state]) {
          hi = t;
        } else {
          lo = t + 1;
        }
      }
    }
  }
  // Overall - O(n*lg(n)^2) \o/
  void ParallelBinarySearch() {
    search_by_state.resize(states_count, {1, showers_count + 1});
    states_by_time.resize(showers_count + 2, {});
    segtree = IterativeSegmentTree<Data>(sectors_count + 1, kNil);
    // O(lg(n))
    while (true) {
      bool has_pending_searches = false;
      for (int state = 0; state < states_count; ++state) {
        const auto [lo, hi] = search_by_state[state];
        if (lo == hi) continue;
        const int mid = (lo + hi) >> 1;
        states_by_time[mid].push_back(state);
        has_pending_searches = true;
      }
      if (!has_pending_searches) break;

      // O(n*lg(n))
      SimulateShowers();

      for (auto& states : states_by_time) states.clear();
      for (auto& di : segtree.data) di = kNil;
      segtree.Build();
    }

    for (int state = 0; state < states_count; ++state) {
      ans_by_state[state] = search_by_state[state].lo;
    }
  }

  bool Run() {
    if (!(std::cin >> states_count >> sectors_count)) return false;
    state_by_sector.resize(sectors_count);
    sectors_by_state.resize(states_count, {});
    for (int sector = 0; sector < sectors_count; ++sector) {
      int& state = state_by_sector[sector];
      std::cin >> state;
      --state;
      sectors_by_state[state].push_back(sector);
    }
    samples_by_state.resize(states_count);
    for (int& si : samples_by_state) std::cin >> si;

    std::cin >> showers_count;
    showers.resize(showers_count);
    for (auto& [l, r, meteors] : showers) {
      std::cin >> l >> r >> meteors;
      --l, --r;
    }

    ans_by_state.resize(states_count);
    ParallelBinarySearch();

    std::ostringstream sout;
    for (const int ans : ans_by_state) {
      if (ans > showers_count) {
        sout << "NIE\n";
      } else {
        sout << ans << "\n";
      }
    }
    std::cout << sout.str();

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
