#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
for every p[i]:
  insert i at p[i]

O(n*sqrt(n)) can be done by maintaining buckets
Definitely not the ideal solution, but sounds interesting to code haha
Surprisingly, on random cases, this runs in 400ms (pretty fast for n = 5e5)

The reverse works (I didn't prove it yet)
in reverse, for every p[i]:
  b[i] = remove element at p[i]
Then, ans = reverse(b)
For example:
  1 1 2 1
  1 2 3 4, remove (1)
  2 3 4, remove (3)
  2 4, remove (2)
  4, remove (4)
Finally, let T[i] be whether i is present or not (1 or 0 respectively)
We can use a segtree to maintain and query the accumulated sum of T
And the element `x` to be removed will be the first where T[0 : x] = p[i]

Usually, I would do a binary search on the segment tree queries O(n*lg^2)
But, it's possible to make that binary search inside the segment tree query to
reduce this to O(n*lg) \o/
Fun fact: in this case, O(n*lg^2) ended-up slower (550ms) because the constant
// is much bigger haha. O(n*lg) is FAST (220ms)

Now... How do I prove that the reverse always works?
*/

struct Data {
  int value;
  Data Merge(const Data& other) const { return Data{value + other.value}; }
};
const Data nil = Data{0};

// DON'T FORGET TO DEFINE THE NIL!!!
template <class T>
struct SegmentTree {
  int size;
  std::vector<T> data;
  std::vector<T> st;
  T nil;
  SegmentTree() {}
  SegmentTree(const int size, const T nil) : size(size), nil(nil) {
    data.resize(size);
    st.resize(4 * size);
  }
  SegmentTree(const std::vector<T>& data, const T nil)
      : size(data.size()), data(data), nil(nil) {
    st.resize(4 * size);
    Build();
  }
  void Build() { Build(1, 0, size - 1); }
  T Query(const int qlo, const int qhi) {
    return Query(qlo, qhi, 1, 0, size - 1);
  }
  int BinQuery(const int target) {
    return BinQuery(target, T{0}, 1, 0, size - 1);
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
  int BinQuery(const int target, const T curr, const int i, const int lo,
               const int hi) {
    if (lo == hi) return lo;
    const int mid = (lo + hi) >> 1;
    const Data curr_plus_left = curr.Merge(st[2 * i]);
    if (curr_plus_left.value >= target)
      return BinQuery(target, curr, 2 * i, lo, mid);
    else
      return BinQuery(target, curr_plus_left, 2 * i + 1, mid + 1, hi);
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

const int kMaxN = 5e5;

struct TestCase {
  int n;
  std::vector<int> p;

  std::vector<std::deque<int>> buckets;

  // O(n*sqrt(n))
  std::vector<int> SolveWithBuckets() {
    buckets.clear();
    // There will be sqrt(n) buckets, each with sqrt(n) elements
    const int sqrt_n = std::sqrt(kMaxN) + 1;
    buckets.resize(sqrt_n, std::deque<int>{});
    for (int i = 0; i < n; ++i) {
      const int bucket_i = p[i] / sqrt_n, bucket_pos = p[i] % sqrt_n;
      buckets[bucket_i].insert(std::next(buckets[bucket_i].begin(), bucket_pos),
                               i);
      for (int j = bucket_i; j + 1 < sqrt_n && (int)buckets[j].size() > sqrt_n;
           ++j) {
        buckets[j + 1].push_front(buckets[j].back());
        buckets[j].pop_back();
      }
    }
    std::vector<int> ans;
    ans.reserve(n);
    for (const auto& bucket : buckets) {
      for (const auto v : bucket) {
        ans.push_back(v);
      }
    }
    return ans;
  }

  // O(n*lg^2)
  std::vector<int> SolveWithSegmentTreeAndInverseProblem() {
    SegmentTree<Data> segtree(std::vector<Data>(n, Data{1}), nil);
    std::vector<int> b;
    for (int i = n - 1; i >= 0; --i) {
      int lo = 0, hi = n - 1;
      while (lo < hi) {
        const int mid = (lo + hi) >> 1;
        if (segtree.Query(0, mid).value > p[i])
          hi = mid;
        else
          lo = mid + 1;
      }
      b.push_back(lo);
      segtree.Update(lo, nil);
    }
    std::reverse(b.begin(), b.end());
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[b[i]] = i;
    }
    return ans;
  }

  // O(n*lg)
  std::vector<int> SolveWithSegmentTreeInternalBinSearchAndInverseProblem() {
    SegmentTree<Data> segtree(std::vector<Data>(n, Data{1}), nil);
    std::vector<int> b;
    for (int i = n - 1; i >= 0; --i) {
      const int x = segtree.BinQuery(p[i] + 1);
      b.push_back(x);
      segtree.Update(x, nil);
    }
    std::reverse(b.begin(), b.end());
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      ans[b[i]] = i;
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    p.resize(n);
    for (auto& pi : p) {
      std::cin >> pi;
      --pi;
    }

    const std::vector<int> ans =
        SolveWithSegmentTreeInternalBinSearchAndInverseProblem();
    assert((int)ans.size() == n);

    for (int i = 0; i < n; ++i) {
      if (i) std::cout << " ";
      std::cout << (ans[i] + 1);
    }
    std::cout << "\n";

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
