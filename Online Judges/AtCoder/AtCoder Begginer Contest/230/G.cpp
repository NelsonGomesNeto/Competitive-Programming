#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
  Data operator*(const int other)
  {
    return Data{value * other};
  }
};
const Data nil = {0};

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
    data.resize(size);
    st.resize(4*size);
    lazy.resize(4*size);
    pending.resize(4*size);
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
    if (pending[i] == 1) // op 1 - add
    {
      st[i] = st[i] + lazy[i];
      if (lo != hi)
      {
        lazy[2*i] = lazy[2*i + 1] = lazy[i];
        pending[2*i] = pending[2*i + 1] = pending[i];
      }
      lazy[i] = nil, pending[i] = 0;
    }
    else if (pending[i] == 2) // op 2 - set
    {
      st[i] = lazy[i] * (hi - lo + 1);
      if (lo != hi)
      {
        lazy[2*i] = lazy[2*i + 1] = lazy[i];
        pending[2*i] = pending[2*i + 1] = pending[i];
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
LazySegtree<Data> segtree;

const int maxN = 2e5; int n;
int p[maxN + 1];
int pos[maxN + 1];

int binarySearch(vector<int> &arr, int target)
{
  if (arr.empty()) return -1;
  int lo = 0, hi = arr.size() - 1;
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (arr[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return arr[lo] <= target ? lo : -1;
}

const int maxX = 2e5;
bool notPrime[maxX + 1];
vector<int> primes;

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  while (~scanf("%d", &n))
  {
    segtree = LazySegtree<Data>(n, nil);
    for (int i = 1; i <= n; i++)
    {
      segtree.data[i - 1] = nil;
      scanf("%d", &p[i]);
      pos[p[i]] = i;
    }
    segtree.build();

    lli ans = n - 2 + (p[1] == 1);
    for (int d: primes)
    {
      if (d > n) break;
      segtree.update(2, 0, d - 1, Data{0});
      for (int k = d; k <= n; k += d)
      {
        if (pos[k] == 1) continue;

        int rem = pos[k] % d;
        int cnt = segtree.query(rem, rem).value;
        ans += cnt;
        DEBUG printf("\t%d %d %d - %d\n", d, k, rem, cnt);
        segtree.update(1, rem, rem, Data{1});
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}