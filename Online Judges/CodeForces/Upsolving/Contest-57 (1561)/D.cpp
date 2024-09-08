#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

// struct Data
// {
//   lli value;
//   Data operator+(const Data &other)
//   {
//     return Data{(value + other.value) % m};
//   }
//   Data operator*(const lli other)
//   {
//     return Data{value * other};
//   }
// };
// const Data nil = Data{0};

// // DON'T FORGET TO DEFINE THE NIL!!!
// template<class T>
// struct LazySegtree
// {
//   int size;
//   T nil;
//   vector<T> data;
//   vector<T> st;
//   vector<T> lazy;
//   vector<int> pending;
//   LazySegtree() { }
//   LazySegtree(int size, T nil) : size(size), nil(nil)
//   {
//     data.resize(size);
//     st.resize(4*size);
//     lazy.resize(4*size);
//     pending.resize(4*size);
//   }
//   LazySegtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
//   {
//     st.resize(4*size);
//     lazy.resize(4*size);
//     pending.resize(4*size);
//     build();
//   }
//   void build() { build(1, 0, size - 1); }
//   T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
//   void update(int op, int ulo, int uhi, T value) { update(op, ulo, uhi, value, 1, 0, size - 1); }
//   void build(int i, int lo, int hi)
//   {
//     if (lo == hi)
//     {
//       st[i] = data[lo];
//       return;
//     }
//     int mid = (lo + hi) >> 1;
//     build(2*i, lo, mid), build(2*i + 1, mid + 1, hi);
//     st[i] = st[2*i] + st[2*i + 1];
//   }
//   void lazyUpdate(int i, int lo, int hi)
//   {
//     if (pending[i])
//     {
//       st[i].value = (st[i].value + lazy[i].value * (hi - lo + 1)) % m;
//       if (lo != hi)
//       {
//         lazy[2*i] = lazy[2*i + 1] = lazy[i];
//         pending[2*i] = pending[2*i + 1] = pending[i];
//       }
//       lazy[i] = nil, pending[i] = 0;
//     }
//   }
//   T query(int qlo, int qhi, int i, int lo, int hi)
//   {
//     lazyUpdate(i, lo, hi);
//     if (hi < qlo || lo > qhi) return nil;
//     if (lo >= qlo && hi <= qhi) return st[i];
//     int mid = (lo + hi) >> 1;
//     return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
//   }
//   void update(int op, int ulo, int uhi, T &value, int i, int lo, int hi)
//   {
//     lazyUpdate(i, lo, hi);
//     if (hi < ulo || lo > uhi) return;
//     if (lo >= ulo && hi <= uhi)
//     {
//       lazy[i] = lazy[i] + value, pending[i] = op;
//       lazyUpdate(i, lo, hi);
//       return;
//     }
//     int mid = (lo + hi) >> 1;
//     update(op, ulo, uhi, value, 2*i, lo, mid), update(op, ulo, uhi, value, 2*i + 1, mid + 1, hi);
//     st[i] = st[2*i] + st[2*i + 1];
//   }
// };
// LazySegtree<Data> lazyseg;

const int maxN = 4e6; int n; lli m;

lli memo[maxN + 1], toacc[maxN + 1];
lli solve(int i = n)
{
  if (i <= 1) return i == 1;
  lli &ans = memo[i];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 1; j <= i; j++)
  {
    if (j < i) ans = (ans + solve(i - j)) % m;
    if (j >= 2) ans = (ans + solve(i / j)) % m;
  }
  return ans;
}
lli solve2()
{
  // lazyseg = LazySegtree<Data>(n, nil);
  // for (int i = 0; i <= n; i++) lazyseg.data[i] = nil;
  // lazyseg.build();
  memset(memo, 0, sizeof(memo));
  memset(toacc, 0, sizeof(toacc));
  memo[1] = 1;
  lli acc = 0;
  for (int i = 1; i <= n; i++)
  {
    acc = (acc + memo[i - 1] + toacc[i]) % m;
    memo[i] = (memo[i] + acc) % m;

    // for (int j = 1; i + j <= n; j++)
    //   memo[i + j] = (memo[i + j] + memo[i]) % m;
    // // ^ could be replaced by a + 1 on range

    for (int j = 2; i * j <= n; j++)
    {
      // for (int k = 0; k < j && i * j + k <= n; k++)
      //   memo[i * j + k] = (memo[i * j + k] + memo[i]) % m;

      toacc[i * j] = (toacc[i * j] + memo[i]) % m;
      if (i * j + (j) <= n)
        toacc[i * j + (j)] = (toacc[i * j + (j)] - memo[i] + m) % m;
    }
  }
  return memo[n];
}

int main()
{
  while (~scanf("%d %lld", &n, &m))
  {
    // memset(memo, -1, sizeof(memo));
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}
