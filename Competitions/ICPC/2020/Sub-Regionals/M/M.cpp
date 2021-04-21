#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  vector<pair<lli, int>> values;
  Data operator+(const Data &other)
  {
    if (values.empty()) return other;
    if (other.values.empty()) return *this;
    Data ans = Data{};
    ans.values.resize(values.size() + other.values.size());
    merge(values.begin(), values.end(), other.values.begin(), other.values.end(), ans.values.begin());
    return ans;
  }
  void put(Data &other, lli yMin)
  {
    for (auto it = lower_bound(other.values.begin(), other.values.end(), make_pair(yMin, -1)); it != other.values.end(); it++)
      values.push_back(*it);
  }
};
Data nil = Data{};

const int maxX = 1e5 + 3;
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
  T query(lli yMin, int qlo, int qhi)
  {
    T ans;
    query(ans, yMin, qlo, qhi, 1, 0, size - 1);
    sort(ans.values.begin(), ans.values.end()); // optional
    return ans;
  }
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
  void query(T &ans, lli yMin, int qlo, int qhi, int i, int lo, int hi)
  {
    if (hi < qlo || lo > qhi) return;
    if (lo >= qlo && hi <= qhi) return ans.put(st[i], yMin);
    int mid = (lo + hi) >> 1;
    query(ans, yMin, qlo, qhi, 2*i, lo, mid);
    query(ans, yMin, qlo, qhi, 2*i + 1, mid + 1, hi);
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

const int maxN = 1e5; int n, q;
const lli mod = 1e9 + 7;
const lli lol = 5782344;

vector<lli> xs;

struct Point
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  void transform()
  {
    // scale y axis be 2, now guns will have a span of 90º (and you will only need integer coordinates)
    // than rotate 45º degrees
    y *= 2;

    // {{cos(a), -sin(a)}, {sin(a), cos(a)}} * {{x}, {y}}
    // (cos(a)*x - sin(a)*y, sin(a)*x + cos(a)*y)
    // cos(45º) = sin(45º) = sqrt(2)/2
    // also scale again by 2 / sqrt(2), so you will continue with only integer coordinates
    lli nx = x - y, ny = x + y;
    x = nx, y = ny;
  }
};
Point enemies[maxN], guns[maxN];
lli ans[maxN];

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli calculate(Point &gun)
{
  int pos = lower_bound(xs.begin(), xs.end(), gun.x) - xs.begin();

  Data res = segtree.query(gun.y, pos, maxX - 1);
  vector<lli> res2;
  for (auto &p: res.values)
    res2.push_back(p.second);
  sort(res2.begin(), res2.end());

  lli sum = 0;
  for (int i = 0; i < res2.size(); i++)
    sum = (sum + res2[i] * modPow(lol, i) % mod) % mod;

  DEBUG
  {
    printf("\tinside (%lld, %lld) | %d:", gun.x, gun.y, pos);
    for (int i = 0; i < res2.size(); i++)
      printf(" %lld", res2[i]);
    printf("\n");
  }
  return sum;
}

int main()
{
  segtree = Segtree<Data>(maxX, nil);

  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; i++)
  {
    enemies[i].read();
    enemies[i].transform();
    xs.push_back(enemies[i].x);
    DEBUG printf("enemy %d: (%lld, %lld)\n", i + 1, enemies[i].x, enemies[i].y);
  }

  sort(xs.begin(), xs.end());
  xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));

  for (int i = 0; i < n; i++)
  {
    int pos = lower_bound(xs.begin(), xs.end(), enemies[i].x) - xs.begin();
    // segtree.update(pos, Data{{{enemies[i].y, i + 1}}});
    segtree.data[pos].values.push_back({enemies[i].y, i + 1});
  }
  for (int i = 0; i < xs.size(); i++)
    sort(segtree.data[i].values.begin(), segtree.data[i].values.end());
  segtree.build();

  for (int i = 0; i < q; i++)
  {
    lli a, b; scanf("%lld %lld", &a, &b);
    lli p = i ? ans[i - 1] : 0;
    guns[i].x = (-1 - ((p + a) % mod));
    guns[i].y = ((p + b) % mod);
    guns[i].transform();
    DEBUG printf("gun %d: (%lld, %lld)\n", i, guns[i].x, guns[i].y);

    ans[i] = calculate(guns[i]);
  }

  for (int i = 0; i < q; i++)
    printf("%lld\n", ans[i]);


  return 0;
}