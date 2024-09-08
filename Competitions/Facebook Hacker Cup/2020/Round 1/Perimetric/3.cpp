#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/* Ideas:
  (Li, 0) -> (Li + Wi, Hi)
  Hi <= Hj, where j > i
    This implies that along with the horizontal delta
    We must also calculate the vertical delta

  Alright, first let's handle the horizontal delta
  For every log:
    get the sum in the x range it occupies
    horizontal delta = x - the sum
    set it's x range
    add horizontal delta to the current perimeter

  Now the vertical delta:
    For every log:
      toRemove += get heights on (Li, Li + Wi)
      
      verticalDelta = toAdd - toRemove

*/
const lli mod = 1e9 + 7;
vector<lli> xs;

struct Data
{
  lli value;
  Data operator+(const Data &other)
  {
    return Data{value + other.value};
  }
  Data operator*(const lli other)
  {
    return Data{value * other};
  }
};
const Data nil = Data{0};

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
  T query(int qlo, int qhi) { if (qlo > qhi) return nil; return query(qlo, qhi, 1, 0, size - 1); }
  void update(int op, int ulo, int uhi, T value) { if (ulo > uhi) return; update(op, ulo, uhi, value, 1, 0, size - 1); }
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
      if (pending[i] == 2)
        st[i] = Data{2LL*(xs[hi + 1] - xs[lo]) % mod};
      else
        st[i] = lazy[i] * (lli)(hi - lo + 1);

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

const int maxN = 1e6; int n, k;
lli al, bl, cl, dl;
lli ah, bh, ch, dh;
lli aw, bw, cw, dw;
struct Room
{
  lli l, h, w;
};
Room rooms[maxN];
lli p[maxN];

map<lli, int> rev;
map<lli, lli> wallsToTheRight, wallsToTheLeft;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < k; i++) scanf("%lld", &rooms[i].l);
    scanf("%lld %lld %lld %lld", &al, &bl, &cl, &dl);
    for (int i = k; i < n; i++) rooms[i].l = (al * rooms[i - 2].l + bl * rooms[i - 1].l + cl) % dl + 1;

    for (int i = 0; i < k; i++) scanf("%lld", &rooms[i].w);
    scanf("%lld %lld %lld %lld", &aw, &bw, &cw, &dw);
    for (int i = k; i < n; i++) rooms[i].w = (aw * rooms[i - 2].w + bw * rooms[i - 1].w + cw) % dw + 1;

    for (int i = 0; i < k; i++) scanf("%lld", &rooms[i].h);
    scanf("%lld %lld %lld %lld", &ah, &bh, &ch, &dh);
    for (int i = k; i < n; i++) rooms[i].h = (ah * rooms[i - 2].h + bh * rooms[i - 1].h + ch) % dh + 1;

    // Compress Coordinates
    rev.clear(), xs.clear();
    for (int i = 0; i < n; i++)
      xs.push_back(rooms[i].l), xs.push_back(rooms[i].l + rooms[i].w);
    sort(xs.begin(), xs.end());
    xs.resize(distance(xs.begin(), unique(xs.begin(), xs.end())));
    for (int i = 0; i < xs.size(); i++)
      rev[xs[i]] = i;

    // Build Inside Points Lazy Segtree (to calculate horizontal delta)
    LazySegtree<Data> insidePointsSegtree = LazySegtree<Data>(xs.size() - 1, nil);
    for (int i = 0; i < xs.size() - 1; i++) insidePointsSegtree.data[i] = Data{0};
    insidePointsSegtree.build();

    // Build Wall Lazy Segtree (to sum all walls height inside a range)
    LazySegtree<Data> wallsSegtree = LazySegtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); i++) wallsSegtree.data[i] = Data{0};
    wallsSegtree.build();

    // Build Height Lazy Segtree (to calculate vertical delta for the walls)
    LazySegtree<Data> heightSegtree = LazySegtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); i++) heightSegtree.data[i] = Data{0};
    heightSegtree.build();

    lli ans = 1;
    wallsToTheRight.clear(), wallsToTheLeft.clear();
    p[0] = 0;
    for (int i = 0; i < n; i++)
    {
      if (i) p[i] = p[i - 1];

      int lo = rev[rooms[i].l], hi = rev[rooms[i].l + rooms[i].w];
      lli horizontalDelta = (2LL*rooms[i].w - insidePointsSegtree.query(lo, hi - 1).value + mod) % mod;
      lli wallsHeightInside = wallsSegtree.query(lo + 1, hi - 1).value;
      lli leftWallDelta = rooms[i].h - max({heightSegtree.query(lo, lo).value, wallsToTheLeft[rooms[i].l], wallsToTheRight[rooms[i].l]});
      lli rightWallDelta = rooms[i].h - max({heightSegtree.query(hi, hi).value, wallsToTheLeft[rooms[i].l + rooms[i].w], wallsToTheRight[rooms[i].l + rooms[i].w]});

      DEBUG printf("\t%d - (%lld %lld) %lld | (%d, %d) | %lld %lld %lld %lld\n",
        i,
        rooms[i].l, rooms[i].l + rooms[i].w, rooms[i].h,
        lo, hi,
        horizontalDelta, wallsHeightInside, leftWallDelta, rightWallDelta);
      DEBUG {
        if (0) printf("\t\tPolygon((%lld, %lld), (%lld, %lld), (%lld, %lld), (%lld, %lld))\n",
        rooms[i].l, 0LL,
        rooms[i].l, rooms[i].h,
        rooms[i].l + rooms[i].w, rooms[i].h,
        rooms[i].l + rooms[i].w, 0LL);
      }

      p[i] = (p[i] - wallsHeightInside + mod) % mod;
      p[i] = (p[i] + horizontalDelta % mod) % mod;
      p[i] = (p[i] + leftWallDelta + rightWallDelta) % mod;
      if (wallsToTheLeft.count(rooms[i].l))
        p[i] = (p[i] - wallsToTheLeft[rooms[i].l] + mod) % mod;
      if (wallsToTheRight.count(rooms[i].l + rooms[i].w))
        p[i] = (p[i] - wallsToTheRight[rooms[i].l + rooms[i].w] + mod) % mod;

      insidePointsSegtree.update(2, lo, hi - 1, Data{1});
      heightSegtree.update(1, lo + 1, hi - 1, Data{rooms[i].h});
      wallsSegtree.update(1, lo, hi, Data{0});
      wallsSegtree.update(1, lo, lo, Data{leftWallDelta});
      wallsSegtree.update(1, hi, hi, Data{rightWallDelta});
      wallsToTheRight[rooms[i].l] = wallsToTheLeft[rooms[i].l + rooms[i].w] = rooms[i].h;
    }

    for (int i = 0; i < n; i++)
      ans = (ans * p[i]) % mod;

    DEBUG {
      printf("L: ");
      for (int i = 0; i < n; i++) printf("%lld%c", rooms[i].l, i < n - 1 ? ' ' : '\n');
      printf("W: ");
      for (int i = 0; i < n; i++) printf("%lld%c", rooms[i].w, i < n - 1 ? ' ' : '\n');
      printf("H: ");
      for (int i = 0; i < n; i++) printf("%lld%c", rooms[i].h, i < n - 1 ? ' ' : '\n');
      printf("P: ");
      for (int i = 0; i < n; i++) printf("%lld%c", p[i], i < n - 1 ? ' ' : '\n');
    }

    printf("Case #%d: %lld\n", tt, ans);
    DEBUG printf("\n");
  }
  return 0;
}