#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
struct Restriction
{
  int a, b, c;
  void read() { scanf("%d %d %d", &a, &b, &c); a--, b--, c--; }
};
Restriction r[maxN];
vector<int> tree[maxN];
bool denied[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) tree[i].clear(), denied[i] = false;

    for (int i = 0; i < m; i++)
    {
      r[i].read();
      denied[r[i].b] = true;
    }

    int root;
    for (int i = 0; i < n; i++)
      if (!denied[i])
        root = i;
    for (int i = 0; i < n; i++)
      if (i != root)
        tree[root].push_back(i);

    for (int i = 0; i < n; i++)
      for (int j: tree[i])
        printf("%d %d\n", i + 1, j + 1);
  }
  return 0;
}
