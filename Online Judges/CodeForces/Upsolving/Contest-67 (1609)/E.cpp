#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct Data
{
  int cnt[3];
  Data operator+(const Data &other)
  {
    Data res = Data{0, 0, 0};
    for (int i = 0; i < 3; i++)
      res.cnt[i] = cnt[i] + other.cnt[i];
    return res;
  }
};
const Data nil = Data{0, 0, 0};
const Data abc[3] = {Data{1, 0, 0}, Data{0, 1, 0}, Data{0, 0, 1}};

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
char s[maxN + 1];
ordered_set<int> pos[3];

struct Query
{
  int pos; char c;
  void read() { scanf("%d %c", &pos, &c); pos--; }
};
Query queries[maxN];

int eval(int l, int r, int delta)
{
  Data now = segtree.query(l, r);
  int res = *min_element(now.cnt, now.cnt+3);
  DEBUG printf("\t%d %d %d - %d\n", l, r, delta, res);
  return delta + res;
}
int eval2(int l, int delta, int ans)
{
  int lo = 0, hi = min({(int)pos[2].size() - 1, ans - 1 - delta, 5});
  while (hi - lo >= 4)
  {
    int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
    int elo = eval(l, *pos[2].find_by_order(pos[2].size() - midlo - 1), midlo + delta), ehi = eval(l, *pos[2].find_by_order(pos[2].size() - midhi - 1), midhi + delta);
    if (elo < ehi) hi = midhi;
    else lo = midlo;
  }
  for (int j = lo; j <= hi; j++)
    ans = min(ans, eval(l, *pos[2].find_by_order(pos[2].size() - j - 1), j + delta));
  return ans;
}

int main()
{
  int pundim = 0;
  while (~scanf("%d %d", &n, &q))
  {
    if (pundim++) printf("--------\n");
    pos[0].clear(), pos[1].clear(), pos[2].clear();

    scanf(" %s", s);
    segtree = Segtree<Data>(n, nil);
    for (int i = 0; i < n; i++)
    {
      segtree.data[i] = abc[s[i] - 'a'];
      pos[s[i] - 'a'].insert(i);
    }
    segtree.build();

    for (int i = 0; i < q; i++)
    {
      queries[i].read();
      int p = queries[i].pos;
      char c = queries[i].c;

      pos[s[p] - 'a'].erase(p);
      pos[c - 'a'].insert(p);
      s[p] = c;
      segtree.update(p, abc[s[p] - 'a']);

      DEBUG printf("\t%s - ", s);

      int ans = 0;
      if (!pos[0].empty() && !pos[2].empty())
      {
        int l = *pos[0].begin();
        int r = *pos[2].rbegin();
        if (l <= r)
        {
          ans = eval(l, r, 0);
          int lo, hi;

          // lo = 0, hi = min((int)pos[0].size() - 1, ans - 1);
          // while (hi - lo >= 4)
          // {
          //   int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
          //   int elo = eval(*pos[0].find_by_order(midlo), r, midlo), ehi = eval(*pos[0].find_by_order(midhi), r, midhi);
          //   if (elo < ehi) hi = midhi;
          //   else lo = midlo;
          // }
          // for (int j = lo; j <= hi; j++)
          //   ans = min(ans, eval(*pos[0].find_by_order(j), r, j));

          // lo = 0, hi = min((int)pos[2].size() - 1, ans - 1);
          // while (hi - lo >= 4)
          // {
          //   int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
          //   int elo = eval(l, *pos[2].find_by_order(pos[2].size() - midlo - 1), midlo), ehi = eval(l, *pos[2].find_by_order(pos[2].size() - midhi - 1), midhi);
          //   if (elo < ehi) hi = midhi;
          //   else lo = midlo;
          // }
          // for (int j = lo; j <= hi; j++)
          //   ans = min(ans, eval(l, *pos[2].find_by_order(pos[2].size() - j - 1), j));

          lo = 0, hi = min({(int)pos[0].size() - 1, ans - 1, 5});
          while (hi - lo >= 4)
          {
            int midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi + 2) / 3;
            int elo = eval2(*pos[0].find_by_order(midlo), midlo, ans), ehi = eval2(*pos[0].find_by_order(midhi), midhi, ans);
            if (elo < ehi) hi = midhi;
            else lo = midlo;
          }
          for (int j = lo; j <= hi; j++)
            ans = min(ans, eval2(*pos[0].find_by_order(j), j, ans));
        }
      }
      printf("%d\n", ans);
    }
  }
  
  return 0;
}
