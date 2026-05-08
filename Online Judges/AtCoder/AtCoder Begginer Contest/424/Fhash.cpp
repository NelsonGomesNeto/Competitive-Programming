#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::random_device rd;
std::mt19937 g(rd());

struct Data {
  std::array<lli, 4> values;
  Data Merge(const Data& other) const {
    Data new_data;
    for (int i = 0; i < 4; ++i)
      new_data.values[i] = values[i] + other.values[i];
    return new_data;
  }
  void Shuffle() { std::shuffle(values.begin(), values.end(), g); }
  Data Neg() const {
    Data new_data;
    for (int i = 0; i < 4; ++i) new_data.values[i] = -values[i];
    return new_data;
  }
  bool Zero() {
    for (int i = 0; i < 4; ++i)
      if (values[i] != 0) return false;
    return true;
  }
};
const Data nil = Data{{0, 0, 0, 0}};

// DON'T FORGET TO DEFINE THE NIL!!!
template <class T>
struct SegmentTree {
  int size;
  std::vector<T> data;
  std::vector<T> st;
  T nil;
  SegmentTree() {}
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
    segtree.Build();

    queries.resize(q);
    for (int i = 0; i < q; ++i) {
      auto& [a, b] = queries[i];
      std::cin >> a >> b;
      --a, --b;
      if (a > b) std::swap(a, b);

      if (!segtree.Query(a, b).Zero()) {
        std::cout << "No\n";
        continue;
      }

      auto hehe = Data{(i + 1) * 10219, (i + 1) * 10007, (i + 1) * 12821,
                       (i + 1) * 90901};
      hehe.Shuffle();
      segtree.Update(a, hehe);
      segtree.Update(b, hehe.Neg());
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
