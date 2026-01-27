#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e6 + 1;

struct Data {
  int mini, maxi;
  Data Merge(const Data& other) const {
    return Data{std::min(mini, other.mini), std::max(maxi, other.maxi)};
  }
};
const Data nil = Data{kInf, 0};

// DON'T FORGET TO DEFINE THE NIL!!!
template <class T>
struct SegmentTree {
  int size;
  std::vector<T> data;
  std::vector<T> st;
  T nil;
  SegmentTree() : SegmentTree(0, nil) {}
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
SegmentTree<Data> segtree;

struct TestCase {
  int n, q;
  std::vector<std::pair<int, int>> queries;
  SegmentTree<Data> segtree;
  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    segtree = SegmentTree<Data>(n, nil);
    for (int i = 0; i < n; ++i) segtree.data[i] = Data{i, i};
    segtree.Build();

    queries.resize(q);
    for (int i = 0; i < q; ++i) {
      auto& [a, b] = queries[i];
      std::cin >> a >> b;
      --a, --b;
      if (a > b) std::swap(a, b);

      const auto [mini, maxi] = segtree.Query(a + 1, b - 1);
      DEBUG std::cout << "\t" << a << " " << b << " | " << mini << " " << maxi
                      << "\n";
      if (mini <= a || maxi >= b) {
        std::cout << "No\n";
        continue;
      }

      segtree.Update(a, Data{b, b});
      segtree.Update(b, Data{a, a});
      std::cout << "Yes\n";
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
