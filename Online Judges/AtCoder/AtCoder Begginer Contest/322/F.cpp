#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  static Data Create(int b) {
    return Data{
      b,
      b == 0, b == 1,
      b, b,
      1, 1,
      1, -1, -1,
      true
    };
  }
  int bit;
  int zero_ans, one_ans;

  int l, r;
  int lcurr, rcurr;
  int sz, lo, hi;
  bool full;
  Data operator+(const Data &other)
  {
    if (bit == -1) return other;
    if (other.bit == -1) return *this;

    int new_zero_ans = max(zero_ans, other.zero_ans);
    int new_one_ans = max(one_ans, other.one_ans);
    int new_lcurr = lcurr;
    int new_rcurr = other.rcurr;
    int new_sz = sz + other.sz;
    if (r == other.l) {
      int comb_size = rcurr + other.lcurr;
      if (r == 1) {
        new_one_ans = max(new_one_ans, comb_size);
      } else {
        new_zero_ans = max(new_zero_ans, comb_size);
      }

      if (full) new_lcurr += other.lcurr;
      if (other.full) new_rcurr += rcurr;
    }

    return Data{
      bit,
      new_zero_ans, new_one_ans,
      l, other.r,
      new_lcurr, new_rcurr,
      new_sz, lo, other.hi,
      full && other.full && r == other.l
    };
  }
  void flip() {
    swap(zero_ans, one_ans);
    bit = !bit, l = !l, r = !r;
  }
  Data operator*(const int other)
  {
    return Data::Create(-1);
  }
};
const Data nil = Data::Create(-1), one = Data::Create(1), zero = Data::Create(0);

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct LazySegtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  vector<T> lazy;
  vector<int> pending;
  LazySegtree() { }
  LazySegtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size, nil);
    st.resize(4*size, nil);
    lazy.resize(4*size, nil);
    pending.resize(4*size, 0);
  }
  LazySegtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int op, int ulo, int uhi, T value) { update(op, ulo, uhi, value, 1, 0, size - 1); }
  void build(int i, int lo, int hi)
  {
    if (lo == hi)
    {
      st[i] = data[lo];
      return;
    }
    int mid = (lo + hi) >> 1;
    build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
  void lazyUpdate(int i, int lo, int hi)
  {
    if (pending[i])
    {
      st[i].flip();
      if (lo != hi) {
        if (pending[2*i]) {
          lazy[2*i] = nil;
          pending[2*i] = 0;
        } else {
          pending[2*i] = pending[i];
        }

        if (pending[2*i + 1]) {
          lazy[2*i + 1] = nil;
          pending[2*i + 1] = 0;
        } else {
          pending[2*i + 1] = pending[i];
        }
      }
      lazy[i] = nil, pending[i] = 0;
    }
  }
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int op, int ulo, int uhi, T &value, int i, int lo, int hi)
  {
    lazyUpdate(i, lo, hi);
    if (hi < ulo || lo > uhi) return;
    if (lo >= ulo && hi <= uhi)
    {
      lazy[i] = value, pending[i] = op;
      lazyUpdate(i, lo, hi);
      return;
    }
    int mid = (lo + hi) >> 1;
    update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
LazySegtree<Data> lazy_seg;

const int kMaxN = 5e5;
int n, q;
char ss[kMaxN + 1];
string s;

int main() {
  int tests = 0;
  while (~scanf("%d %d", &n, &q)) {
    if (tests++) printf("--------------------------\n");
    scanf(" %s", ss);
    s = string(ss);

    lazy_seg = LazySegtree<Data>(n, nil);
    for (int i = 0; i < n; ++i) {
      lazy_seg.data[i] = s[i] == '1' ? one : zero;
      lazy_seg.data[i].lo = lazy_seg.data[i].hi = i;
    }
    lazy_seg.build();

    for (int i = 0; i < q; ++i) {
      int op, lo, hi;
      scanf("%d %d %d", &op, &lo, &hi);
      --lo, --hi;
      if (op == 1) {
        lazy_seg.update(1, lo, hi, Data::Create(1));
      } else {
        Data res = lazy_seg.query(lo, hi);
        DEBUG {
          string a;
          for (int j = lo; j <= hi; ++j)
            a += to_string(lazy_seg.query(j, j).bit);
          printf("\t%s\n", a.c_str());
          printf("\t%d |%d %d| %d %d %d %d %d\n", res.bit, res.zero_ans, res.one_ans, res.l, res.lcurr, res.r, res.rcurr, res.full);
        }
        printf("%d\n", res.one_ans);
      }
    }
  }
  return 0;
}
