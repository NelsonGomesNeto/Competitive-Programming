#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007
#define PI acos(-1)

namespace geo
{
  struct pt
  {
    int x, y;
    pt operator+(pt p) { return {x + p.x, y + p.y}; } // soma de pontos
    pt operator-(pt p) { return {x - p.x, y - p.y}; } // subtração de pontos
    pt operator*(int d) { return {x * d, y * d}; }    // multiplicação por um int
    pt operator/(int d) { return {x / d, y / d}; }    // divisão por um int
  };
  int dot(pt v, pt w) // produto escalar (dot product)
  {
    return v.x * w.x + v.y * w.y;
  }
  bool is_perp(pt v, pt w) // retorna se dois vetores sao perpendiculares (angulo 90 graus)
  {
    return dot(v, w) == 0;
  }
  int cross(pt v, pt w) // produto vetorial (cross product)
  {
    return v.x * w.y - v.y * w.x;
  }
  int dist(pt a, pt b) // retorna o quadrado da distancia entre dois pontos
  {
    pt c = a - b;
    return c.x * c.x + c.y * c.y;
  }
  bool is_colinear(pt a, pt b, pt c) // retorna se os pontos a, b e c são colineares
  {
    return cross(b - a, c - a) == 0;
  }
  bool ccw(pt a, pt b, pt c) // retorna se os pontos a,b e c estão no sentido anti horario
  {
    return cross(b - a, c - b) > 0;
  }
  bool cw(pt a, pt b, pt c) // retorna se os pontos a,b e c estão no sentido horario
  {
    return cross(b - a, c - b) < 0;
  }
  int modulo(pt v) // |v| = sqrt(x² + y²)
  {
    return sqrt(v.x * v.x + v.y * v.y);
  }
  int angle(pt a, pt b, pt c) // angulo entre os vetores ab e ac
  {
    // dot(ab , ac) / |ab| * |ac|
    pt ab = b - a; // vetor ab
    pt ac = c - a; // vetor ac
    int m1 = modulo(ab);
    int m2 = modulo(ac);
    int m3 = m1 * m2;
    return (dot(ab, ac) / m3); // retorna o cos do angulo em graus
  }
  pt rotate(pt p, int a) // rotacionar o ponto p em relação a origem, em a graus, no sentido anti-horario
  {
    a = (a * PI) / 180;
    int xx = (cos(a) * p.x) + ((sin(a) * -1) * p.y);
    int yy = (sin(a) * p.x) + (cos(a) * p.y);
    pt ans = {xx, yy};
    return ans;
  }
  int polar(pt p) // polar angle
  {
    return atan2l(p.y, p.x);
  }
  bool cmp(pt a, pt b) // ordenar pontos pelo polar angle
  {
    return polar(a) < polar(b);
  }
  bool cmp_x(pt a, pt b) // ordenar os pontos pela coordenada x
  {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  }
  vector<pt> convex_hull(vector<pt> v)
  {
    sort(v.begin(), v.end(), cmp_x);
    pt p1 = v[0], p2 = v.back();
    vector<pt> up;
    vector<pt> down;
    up.pb(p1);
    down.pb(p1);
    for (int i = 1; i < v.size(); i++)
    {
      if (i == v.size() - 1 || cw(p1, v[i], p2))
      {
        while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], v[i]))
          up.pop_back();
        up.pb(v[i]);
      }
    }
    for (int i = 1; i < v.size(); i++)
    {
      if (i == v.size() - 1 || ccw(p1, v[i], p2))
      {
        while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], v[i]))
          down.pop_back();
        down.pb(v[i]);
      }
    }
    int start = 0, limit = 0; // para por em ans no sentido anti-horario e a partir de start
    for (int i = 1; i < down.size(); i++)
    {
      if ((down[i].x < down[start].x) || (down[i].x == down[start].x && down[i].y < down[start].y))
        start = i;
    }
    if (!start)
      limit = 1;
    vector<pt> ans;
    for (int i = start; i < down.size() - 1; i++)
      ans.pb(down[i]);
    for (int i = up.size() - 1; i >= limit; i--)
      ans.pb(up[i]);
    for (int i = 1; i < start; i++)
      ans.pb(down[i]);
    return ans;
  }
}

const int inf = 1e18;

void solve()
{
  int n, k, d;
  cin >> n >> k >> d;
  d *= d;
  vector<geo::pt> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].x >> v[i].y;
  vector<geo::pt> ch = geo::convex_hull(v);
  n = ch.size();
  vector<bool> vis(n, 0);
  vector<int> dist(n, inf);
  vector<bool> in(n, 0);
  in[0] = 1;
  dist[0] = 0;
  while (1)
  {
    int x = -1;
    for (int i = 0; i < n; i++)
    {
      if (in[i])
      {
        if (x == -1)
          x = i;
        else if (dist[i] < dist[x])
          x = i;
      }
    }
    if (x == -1)
      break;
    in[x] = 0;
    if (vis[x])
      continue;
    vis[x] = 1;
    for (int i = 0; i < n; i++)
    {
      int dd = geo::dist(ch[i], ch[x]);
      if (dd > d)
        continue;
      dd = max(dd, k);
      if (dist[i] > dist[x] + dd)
      {
        dist[i] = dist[x] + dd;
        in[i] = 1;
      }
    }
  }
  int id;
  for (int i = 0; i < n; i++)
  {
    if (v.back().x == ch[i].x && v.back().y == ch[i].y)
      id = i;
  }
  (dist[id] == inf) ? cout << "-1\n" : cout << dist[id] << endl;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++)
  {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
// custo de (a, c) para (b, d):
// max(k, (a - c)^2 + (b - d)^2) + dp[(a, c)]

// posso ir se:
// (a - c)^2 + (b - d)^2 <= d
// existe um half-plane que contem somente o ponto (b, d)

// como checar se existe um half-plane que contem somente o ponto (a, b)?
// convex-hull?
// e depois de descobrir os pontos validos
// como acho esse shortest path?
// estilo dijkstra?