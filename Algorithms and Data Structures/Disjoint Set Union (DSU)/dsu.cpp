#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct DSU {
  int size;
  std::vector<int> parents;
  DSU() : size(0) { parents.clear(); }
  DSU(const int sz) : size(sz) { Init(); }
  void Init() { parents.resize(size, -1); }
  int Root(const int u) {
    return parents[u] < 0 ? u : parents[u] = Root(parents[u]);
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) std::swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int SetSize(const int u) { return -parents[Root(u)]; }
  bool SameSet(const int u, const int v) { return Root(u) == Root(v); }
};
DSU dsu;

int main() {
  int n, q;
  while (scanf("%d %d", &n, &q) != EOF) {
    dsu = DSU(n);
    for (int i = 0; i < q; i++) {
      char op;
      scanf(" %c", &op);
      if (op == 'U') {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        dsu.Merge(u, v);
        printf("Merged %d, %d\n", u + 1, v + 1);
      } else if (op == 'S') {
        int u;
        scanf("%d", &u);
        u--;
        printf("%d setSize: %d\n", u + 1, dsu.SetSize(u));
      } else {
        int u, v;
        scanf("%d %d", &u, &v);
        u--, v--;
        printf("sameSet(%d, %d): %d\n", u + 1, v + 1, dsu.SameSet(u, v));
      }
    }
  }
  return 0;
}