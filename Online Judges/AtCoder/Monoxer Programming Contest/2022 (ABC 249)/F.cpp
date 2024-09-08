#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int cnt; lli value; lli sum;
  Data operator+(const Data &other)
  {
    return Data{cnt + other.cnt, value + other.value, sum + other.sum};
  }
};
const Data nil = Data{0, 0, 0};

// DON'T FORGET TO DEFINE THE NIL!!!
template<class T>
struct Segtree
{
  int size;
  T nil;
  vector<T> data;
  vector<T> st;
  Segtree() { }
  Segtree(int size, T nil) : size(size), nil(nil)
  {
    data.resize(size, nil);
    st.resize(4*size);
  }
  Segtree(vector<T> &data, T nil) : size(data.size()), data(data), nil(nil)
  {
    st.resize(4*size);
    build();
  }
  void build() { build(1, 0, size - 1); }
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
  void update(int pos, T value) { update(pos, value, 1, 0, size - 1); }
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
  T query(int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return nil;
    if (lo >= qlo && hi <= qhi) return st[i];
    int mid = (lo + hi) >> 1;
    return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
  }
  void update(int pos, T &value, int i, int lo, int hi)
  {
    if (lo == hi)
    {
      // st[i] = data[lo] = value;
      st[i].cnt += value.cnt;
      st[i].value = value.value;
      st[i].sum += value.sum;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

/*
last t2 operation will have [0, k] operations to skip
the one before that will have [0, k - 1] operations to skip

t2[-i] max[k - i] operations to skip
*/

const int maxN = 2e5; int n, k;
int t[maxN + 1]; lli y[maxN + 1];
vector<lli> ys;

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    ys.clear();
    t[0] = 1, y[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
      scanf("%d %lld", &t[i], &y[i]);
      if (t[i] == 2 && y[i] < 0) ys.push_back(y[i]);
    }
    lli ans = 0;
    for (int i = n; i >= 0; --i)
    {
      if (t[i] == 1)
      {
        ans = y[i];
        for (int j = i; j <= n; ++j)
          if (t[j] == 2)
            ans += y[j];
        break;
      }
    }

    sort(ys.begin(), ys.end());
    ys.resize(distance(ys.begin(), unique(ys.begin(), ys.end())));
    segtree = Segtree<Data>(ys.size(), nil);
    if (!ys.empty()) segtree.build();

    lli sum = 0;
    int remSkip = k;
    for (int i = n; i >= 0; --i)
    {
      if (t[i] == 1)
      {
        lli skippedSum = 0;
        if (remSkip > 0 && !ys.empty())
        {
          int lo = 0, hi = ys.size() - 1;
          while (lo < hi)
          {
            int mid = (lo + hi) >> 1;
            if (segtree.query(0, mid).cnt >= remSkip) hi = mid;
            else lo = mid + 1;
          }
          Data hehe = segtree.query(0, lo);
          skippedSum = hehe.sum;
          if (hehe.cnt > remSkip)
            skippedSum -= (hehe.cnt - remSkip) * ys[lo];
        }
        ans = max(ans, y[i] + sum - skippedSum);
        if (--remSkip < 0)
          break;
      }
      else
      {
        sum += y[i];
        if (y[i] < 0)
          segtree.update(lower_bound(ys.begin(), ys.end(), y[i]) - ys.begin(), Data{1, y[i], y[i]});
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
