#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Data {
  int value;
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
SegmentTree<Data> segtree;

int main() {
  int n;
  std::cin >> n;
  segtree = SegmentTree<Data>(n, kNil);
  for (int i = 0; i < n; i++) std::cin >> segtree.data[i].value;
  segtree.Build();

  char kind;
  while (std::cin >> kind) {
    if (kind == 'Q') {
      int lo, hi;
      std::cin >> lo >> hi;
      std::println("Sum({}, {}) = {}", lo, hi, segtree.Query(lo, hi).value);
    } else if (kind == 'U') {
      int pos, value;
      std::cin >> pos >> value;
      segtree.Update(pos, Data{value});
      std::println("Update({} with {})", pos, value);
    }
  }
  return (0);
}
