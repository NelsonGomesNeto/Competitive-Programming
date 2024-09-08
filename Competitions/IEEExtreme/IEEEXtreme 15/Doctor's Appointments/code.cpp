#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
struct Patient
{
  int l, r, idx;
  void read() { scanf("%d %d", &l, &r); l--, r--; }
  bool operator<(const Patient &other) const { return r > other.r || (r == other.r && l > other.l); }
};
Patient p[maxN];
int ans[maxN];
bool onQueue[maxN];
vector<int> in[maxN], out[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
      ans[i] = -1;
      in[i].clear(), out[i].clear();
      onQueue[i] = false;
    }

    for (int i = 0; i < n; i++)
    {
      p[i].read(), p[i].idx = i;
      in[p[i].l].push_back(i), out[p[i].r].push_back(i);
    }
    // sort(p, p+n);

    priority_queue<Patient> pq;
    for (int i = 0; i < n; i++)
    {
      for (int j: in[i]) pq.push(p[j]), onQueue[j] = true;

      if (pq.empty()) break;

      ans[i] = pq.top().idx;
      pq.pop(), onQueue[ans[i]] = false;

      bool valid = true;
      for (int j: out[i]) if (onQueue[j]) valid = false;
      if (!valid) break;
    }

    if (*min_element(ans, ans+n) == -1) printf("impossible\n");
    else for (int i = 0; i < n; i++) printf("%d%c", ans[i] + 1, i + 1 < n ? ' ' : '\n');
  }
  return 0;
}