#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
ans_by_state[i] = T after which an state will have >= requires samples
*/

struct Data {
  lli value;
  Data Merge(const Data& other) const { return Data{value + other.value}; }
};
// DON'T FORGET TO DEFINE THE NIL!!!
const Data kNil = Data{0};

template <class T>
struct SegmentTree {
  int size;
  std::vector<T> data;
  std::vector<T> st;
  T nil;
  SegmentTree() : SegmentTree(/*size=*/0, nil) {}
  SegmentTree(const int size_, const T nil_) : size(size_), nil(nil_) {
    data.resize(size, nil);
    st.resize(4 * size);
  }
  SegmentTree(const std::vector<T>& data_, const T nil_)
      : size(data_.size()), data(data_), nil(nil_) {
    st.resize(4 * size);
    Build();
  }
  void Build() { Build(1, 0, size - 1); }
  T Query(const int qlo, const int qhi) {
    return Query(qlo, qhi, 1, 0, size - 1);
  }
  void Update(const int pos, const T& value) {
    Update(pos, value, 1, 0, size - 1);
  }
  void Build(const int i, const int lo, const int hi) {
    if (lo == hi) {
      st[i] = data[lo];
      return;
    }
    const int mid = (lo + hi) >> 1;
    Build(2 * i, lo, mid), Build(2 * i + 1, mid + 1, hi);
    st[i] = st[2 * i].Merge(st[2 * i + 1]);
  }
  T Query(const int qlo, const int qhi, const int i, const int lo,
          const int hi) {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    const int mid = (lo + hi) >> 1;
    return Query(qlo, qhi, 2 * i, lo, mid)
        .Merge(Query(qlo, qhi, 2 * i + 1, mid + 1, hi));
  }
  void Update(const int pos, const T& value, const int i, const int lo,
              const int hi) {
    if (lo == hi) {
      st[i] = data[lo] = value;
      return;
    }
    const int mid = (lo + hi) >> 1;
    if (pos <= mid)
      Update(pos, value, 2 * i, lo, mid);
    else
      Update(pos, value, 2 * i + 1, mid + 1, hi);
    st[i] = st[2 * i].Merge(st[2 * i + 1]);
  }
};

struct TestCase {
  int states_count, sectors_count;
  std::vector<int> state_by_sector;
  std::vector<int> samples_by_state;
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
  SegmentTree<Data> segtree;
  void SimulateShowers() {
    // TODO: Optimize this RangeUpdate \o/.
    std::vector<int> sum_by_state(states_count, 0);
    const auto RangeUpdate = [&](const int lo, const int hi,
                                 const int meteors) {
      for (int p = lo; p <= hi; ++p) {
        sum_by_state[state_by_sector[p]] += meteors;
      }
    };
    for (const auto [i, shower] : showers | std::views::enumerate) {
      const int t = i + 1;
      const auto [l, r, meteors] = shower;
      if (l > r) {
        RangeUpdate(0, r, meteors), RangeUpdate(l, sectors_count - 1, meteors);
      } else {
        RangeUpdate(l, r, meteors);
      }

      for (const auto state : states_by_time[t]) {
        auto& [lo, hi] = search_by_state[state];
        DEBUG std::println("{} - [{} : {}] | {} >= {}", state, lo, hi,
                           sum_by_state[state], samples_by_state[state]);
        if (sum_by_state[state] >= samples_by_state[state]) {
          hi = t;
        } else {
          lo = t + 1;
        }
      }
    }
  }
  void ParallelBinarySearch() {
    search_by_state.resize(states_count, {1, showers_count + 1});
    states_by_time.resize(showers_count + 2, {});
    segtree = SegmentTree<Data>(sectors_count, kNil);
    while (true) {
      // TODO: Consider optimizing this iteration through the pending searches.
      bool has_pending_searches = 0;
      for (const auto [state, params] :
           search_by_state | std::views::enumerate) {
        const auto [lo, hi] = params;
        if (lo == hi) continue;
        const int mid = (lo + hi) >> 1;
        states_by_time[mid].push_back(state);
        has_pending_searches = true;
      }
      if (!has_pending_searches) break;

      SimulateShowers();

      // TODO: Consider replacing this by clearing the vectors instead.
      std::ranges::fill(states_by_time, std::vector<int>{});
      std::ranges::fill(segtree.data, kNil);
      segtree.Build();
    }

    for (const auto [state, params] : search_by_state | std::views::enumerate) {
      ans_by_state[state] = params.lo;
      DEBUG std::println("{} = {}", state, ans_by_state[state]);
    }
  }

  bool Run() {
    if (!(std::cin >> states_count >> sectors_count)) return false;
    state_by_sector.resize(sectors_count);
    for (int& si : state_by_sector) {
      std::cin >> si;
      --si;
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
        std::println(sout, "NIE");
      } else {
        std::println(sout, "{}", ans);
      }
    }
    std::print("{}", sout.str());

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
