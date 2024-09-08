#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Data
{
  int cnt, value; lli total;
  Data operator+(const Data &other)
  {
    return Data{cnt + other.cnt, -1, total + other.total};
  }
};
const Data nil = Data{0, 0};

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
      st[i].cnt += value.cnt;
      st[i].total = (lli)st[i].cnt * st[i].value;
      return;
    }
    int mid = (lo + hi) >> 1;
    if (pos <= mid) update(pos, value, 2*i, lo, mid);
    else update(pos, value, 2*i + 1, mid + 1, hi);
    st[i] = st[2*i] + st[2*i + 1];
  }
};
Segtree<Data> aseg, bseg;

const int maxN = 2e5; int n, m, q;
struct Query
{
  int t, x, y;
  void read() { scanf("%d %d %d", &t, &x, &y); x--; }
};
Query queries[maxN];
int a[maxN], b[maxN];
vector<int> ys;
map<int, int> yIdx;

int main()
{
  int tt = 0;
  while (~scanf("%d %d %d", &n, &m, &q))
  {
    if (tt++) printf("--------------------\n");

    memset(a, 0, sizeof(a)), memset(b, 0, sizeof(b));
    ys.clear();
    ys.push_back(0);
    for (int i = 0; i < q; i++)
    {
      queries[i].read();
      ys.push_back(queries[i].y);
    }

    sort(ys.begin(), ys.end());
    ys.resize(distance(ys.begin(), unique(ys.begin(), ys.end())));
    for (int i = 0; i < ys.size(); i++)
      yIdx[ys[i]] = i;

    aseg = Segtree<Data>(ys.size(), nil), bseg = Segtree<Data>(ys.size(), nil);
    for (int i = 0; i < ys.size(); i++)
      aseg.data[i] = bseg.data[i] = Data{0, ys[i], 0};
    aseg.data[0] = Data{n, 0, 0}, bseg.data[0] = Data{m, 0, 0};
    aseg.build(), bseg.build();

    lli ans = 0;
    for (int i = 0; i < q; i++)
    {
      if (queries[i].t == 1)
      {
        aseg.update(yIdx[a[queries[i].x]], Data{-1, 0, 0});

        lli prv = (lli)bseg.query(0, yIdx[a[queries[i].x]]).cnt * a[queries[i].x]
                     + bseg.query(yIdx[a[queries[i].x]] + 1, ys.size() - 1).total;

        a[queries[i].x] = queries[i].y;
        lli now = (lli)bseg.query(0, yIdx[a[queries[i].x]]).cnt * a[queries[i].x]
                     + bseg.query(yIdx[a[queries[i].x]] + 1, ys.size() - 1).total;
        ans += now - prv;

        aseg.update(yIdx[a[queries[i].x]], Data{1, 0, 0});
      }
      else
      {
        bseg.update(yIdx[b[queries[i].x]], Data{-1, 0, 0});

        lli prv = (lli)aseg.query(0, yIdx[b[queries[i].x]]).cnt * b[queries[i].x]
                     + aseg.query(yIdx[b[queries[i].x]] + 1, ys.size() - 1).total;

        b[queries[i].x] = queries[i].y;
        lli now = (lli)aseg.query(0, yIdx[b[queries[i].x]]).cnt * b[queries[i].x]
                     + aseg.query(yIdx[b[queries[i].x]] + 1, ys.size() - 1).total;
        ans += now - prv;

        bseg.update(yIdx[b[queries[i].x]], Data{1, 0, 0});
      }

      DEBUG {
        printf("\ta: ");
        for (int j = 0; j < n; j++)
          printf("%d%c", a[j], j < n - 1 ? ' ' : '\n');
        printf("\tb: ");
        for (int j = 0; j < m; j++)
          printf("%d%c", b[j], j < m - 1 ? ' ' : '\n');
      }

      printf("%lld\n", ans);
    }
  }
  return 0;
}