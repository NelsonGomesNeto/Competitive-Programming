#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x, y;
char s[maxN + 1];
vector<int> options;

struct Data
{
  int ones, zeros;
  Data operator+(const Data &other)
  {
    return Data{ones + other.ones, zeros + other.zeros};
  }
};
const Data nil = Data{0, 0};

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
    data.resize(size);
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
      st[i] = data[lo] = value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> segtree;

lli getTotal(int i, char v)
{
  lli total = 0;
  if (i)
  {
    Data res = segtree.query(0, i - 1);
    if (v == '1')
      total += x * res.zeros;
    else
      total += y * res.ones;
  }
  if (i + 1 < n)
  {
    Data res = segtree.query(i + 1, n - 1);
    if (v == '1')
      total += y * res.zeros;
    else
      total += x * res.ones;
  }
  return total;
}
lli getDelta(int i)
{
  return s[i] == '1' ? getTotal(i, '0') - getTotal(i, '1') : getTotal(i, '1') - getTotal(i, '0');
}

struct Node
{
  lli delta; int i, version;
  bool operator<(const Node &other) const { return delta > other.delta; }
};

int main()
{
  while (~scanf(" %s", s))
  {
    n = strlen(s);
    scanf("%lld %lld", &x, &y);
    options.clear();
    for (int i = 0; i < n; i++)
      if (s[i] == '?')
        options.push_back(i);

    lli ans = LONG_LONG_MAX;
    for (char op = '0'; op <= '1'; op++)
    {
      for (int i: options)
          s[i] = op;

      segtree = Segtree<Data>(n, nil);
      for (int i = 0; i < n; i++)
        segtree.data[i] = Data{s[i] == '1', s[i] == '0'};
      segtree.build();

      priority_queue<Node> pq;
      int version = 0;
      while (true)
      {
        bool has = false;
        for (int i: options)
        {
          lli delta = getDelta(i);
          DEBUG printf("\t%d %c %lld || %lld %lld\n", i, s[i], delta, getTotal(i, '1'), getTotal(i, '0'));
          pq.push({delta, i, version});
          if (delta < 0) has = true;
        }
        if (!has) break;
        while (!pq.empty())
        {
          auto u = pq.top(); pq.pop();
          if (u.version == version)
          {
            if (u.delta < 0)
            {
              s[u.i] = s[u.i] == '1' ? '0' : '1';
              segtree.update(u.i, Data{s[u.i] == '1', s[u.i] == '0'});
              version++;
              pq.push({getDelta(u.i), u.i, version});
            }
          }
          else
            pq.push({getDelta(u.i), u.i, version});
        }
      }

      lli curr = 0;
      for (int i = 0; i + 1 < n; i++)
        if (s[i] == '1')
          curr += y * segtree.query(i + 1, n - 1).zeros;
        else
          curr += x * segtree.query(i + 1, n - 1).ones;
      ans = min(ans, curr);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
