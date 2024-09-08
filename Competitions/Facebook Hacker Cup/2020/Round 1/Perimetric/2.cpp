#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Ideas:
  (Li, 0) -> (Li + Wi, Hi)
  Hi >= Hj, where j > i
    This implies that we're never going to have to consider vertical delta
    Only horizontal deltas

  So, if it connects:
    + horizontal delta
    - vertical delta
      some vertical perimeter will be lost
        I need to count how many flips happened in the queried range
        I also need to know if a wall is covered
    + 2*h
  else:
    + new perimeter

  Compress coordinates, lazy segtree, gg

  Instead of making a segtree with the exiting coordinates
  Make a segtree with the coordinates in between
  And initially store the distance that point will represent (xj - xi)
  So when querying, we always get the horizontal delta
  When updating, we set all those coordinates between lo and hi to 0

  The only problem is that when two rooms share a wall, the horizontal delta
  will be equal to the horizontal delta of the full room.
  To go around that, we can store in a set every wall; if a wall is already
  and the delta == full room: we've hitted the case were two rooms share a wall
*/

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
  T query(int qlo, int qhi) { return query(qlo, qhi, 1, 0, size - 1); }
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
const lli mod = 1e9 + 7;
lli al, bl, cl, dl;
lli ah, bh, ch, dh;
lli aw, bw, cw, dw;
struct Room
{
  lli l, h, w;
};
Room rooms[maxN];
lli p[maxN];

vector<lli> xs;
map<lli, int> rev;
set<lli> wallsToTheRight, wallsToTheLeft;

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
    for (int i = 1; i < xs.size(); i++) insidePointsSegtree.data[i - 1] = Data{xs[i] - xs[i - 1]};
    insidePointsSegtree.build();

    // Build Wall Lazy Segtree (to count the walls inside a range)
    LazySegtree<Data> wallsSegtree = LazySegtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); i++) wallsSegtree.data[i] = Data{0};
    wallsSegtree.build();

    // Build Covered Lazy Segtree (to check if a wall is covered)
    LazySegtree<Data> coveredSegtree = LazySegtree<Data>(xs.size(), nil);
    for (int i = 0; i < xs.size(); i++) coveredSegtree.data[i] = Data{0};
    coveredSegtree.build();

    lli ans = 1;
    wallsToTheRight.clear(), wallsToTheLeft.clear();
    p[0] = 0;
    for (int i = 0; i < n; i++)
    {
      if (i) p[i] = p[i - 1];

      int lo = rev[rooms[i].l], hi = rev[rooms[i].l + rooms[i].w];
      lli hDelta = insidePointsSegtree.query(lo, hi - 1).value;
      lli wallsInside = wallsSegtree.query(lo, hi).value;
      lli leftWallCovered = coveredSegtree.query(lo, lo).value > 0 || wallsToTheLeft.count(rooms[i].l);
      lli rightWallCovered = coveredSegtree.query(hi, hi).value > 0 || wallsToTheRight.count(rooms[i].l + rooms[i].w);

      DEBUG printf("\t%d - (%lld %lld) %lld | (%d, %d) | %lld %lld %lld %lld\n",
        i,
        rooms[i].l, rooms[i].l + rooms[i].w, rooms[i].h,
        lo, hi,
        hDelta, wallsInside, leftWallCovered, rightWallCovered);
      DEBUG {
        if (0) printf("\t\tPolygon((%lld, %lld), (%lld, %lld), (%lld, %lld), (%lld, %lld))\n",
        rooms[i].l, 0LL,
        rooms[i].l, rooms[i].h,
        rooms[i].l + rooms[i].w, rooms[i].h,
        rooms[i].l + rooms[i].w, 0LL);
      }

      if (hDelta == 0) // fully contained
        p[i] += 0;
      else if (hDelta == rooms[i].w && !wallsToTheRight.count(rooms[i].l) && !wallsToTheRight.count(rooms[i].l + rooms[i].w)
                                    && !wallsToTheLeft.count(rooms[i].l) && !wallsToTheLeft.count(rooms[i].l + rooms[i].w)) // doesn't share a wall
        p[i] = (p[i] + 2LL*rooms[i].w % mod + 2LL*rooms[i].h) % mod;
      else
        p[i] = (p[i]
                + 2LL*hDelta % mod
                - wallsInside*rooms[i].h % mod
                + (leftWallCovered ? 0LL : rooms[i].h)
                + (rightWallCovered ? 0LL : rooms[i].h)
                + mod) % mod;

      insidePointsSegtree.update(1, lo, hi - 1, Data{0});
      coveredSegtree.update(1, lo + 1, hi - 1, Data{1});
      wallsSegtree.update(1, lo, hi, Data{0});
      if (!leftWallCovered) wallsSegtree.update(1, lo, lo, Data{1});
      if (!rightWallCovered) wallsSegtree.update(1, hi, hi, Data{1});
      wallsToTheRight.insert(rooms[i].l), wallsToTheLeft.insert(rooms[i].l + rooms[i].w);
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