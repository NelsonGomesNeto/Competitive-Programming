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
    st[pos + size] = data[pos] = value;
    for (int i = (pos + size) >> 1; i; i >>= 1)
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
  return 0;
}