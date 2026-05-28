#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Brilliant O(trust) hahahaha

### Idea
"a mod x" has only 2 options:
a < x -> nothing changes
a >= x -> a becomes < x

If you think deepily, a >= x will *at least* divide a by 2.
That's because for `a` to become `x - 1`, it has to be (k*x + (x - 1)).
So, for any `k`, `a` will be *at least* divided by 2.

So, in the worst case, we need O(lg(n)) "a mod x" operations to reduce any
number to 1.

Which leads us to O(n*lg(n)) to do that for all numbers.

### Solution
"a mod x" operation:
  Use a Segtree to find the maximum in a range.
  Update each maximum individually until all values are less than x.
Use the same Segtree to find the sum in a range.
That's it hahahaha.
*/

struct Data {
  lli sum;
  int max, pos;
  Data Merge(const Data& other) const {
    if (max > other.max)
      return Data{sum + other.sum, max, pos};
    else
      return Data{sum + other.sum, other.max, other.pos};
  }
};
// DON'T FORGET TO DEFINE THE NIL!!!
const Data kNil = Data{0, -1, -1};

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

struct TestCase {
  int n, m;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    SegmentTree<Data> segtree(n, kNil);
    for (int i = 0; i < n; ++i) {
      segtree.data[i] = Data{a[i], a[i], i};
    }
    segtree.Build();
    for (int qi = 0; qi < m; ++qi) {
      int t;
      std::cin >> t;
      int l, r, x;
      if (t == 1) {
        std::cin >> l >> r;
        --l, --r;
        std::println("{}", segtree.Query(l, r).sum);
      } else if (t == 2) {
        std::cin >> l >> r >> x;
        --l, --r;
        while (true) {
          if (const auto [_, max, pos] = segtree.Query(l, r); max >= x) {
            const int new_value = max % x;
            segtree.Update(pos, Data{new_value, new_value, pos});
          } else
            break;
        }
      } else {
        int k;
        std::cin >> k >> x;
        --k;
        segtree.Update(k, Data{x, x, k});
      }
    }
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
