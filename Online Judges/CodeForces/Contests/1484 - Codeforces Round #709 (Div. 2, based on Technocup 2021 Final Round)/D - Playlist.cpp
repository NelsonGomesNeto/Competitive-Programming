#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

// gcd(a, b) == 1
struct SongPair
{
  int lo, hi;
  bool operator<(const SongPair &other) const { return lo < other.lo; }
};
vector<int> ans;
set<int> alive;
set<SongPair> songPairs;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    alive.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      alive.insert(i);
    }

    songPairs.clear();
    for (int i = 0; i < n; i++)
      if (gcd(a[i], a[(i + 1) % n]) == 1)
      {
        // DEBUG printf("\tbuilding: %d %d\n", i, (i + 1) % n);
        songPairs.insert(SongPair{i, (i + 1) % n});
      }

    ans.clear();
    int curr = 0;
    while (!songPairs.empty())
    {
      // DEBUG printf("\t\t%d || %d || %d\n", curr + 1, (int)songPairs.size(), songPairs.begin()->lo);
      auto it = songPairs.lower_bound(SongPair{curr, 0});
      if (it != songPairs.end())
      {
        SongPair now = *it;
        // DEBUG printf("\t\tremoving: %d || %d %d || %lld %lld\n", curr + 1, now.lo + 1, now.hi + 1, a[now.lo], a[now.hi]);
        songPairs.erase(it);
        alive.erase(now.hi);
        ans.push_back(now.hi);
        curr = (now.hi + 1) % n;

        auto hisp = songPairs.lower_bound(SongPair{now.hi, 0});
        if (hisp != songPairs.end() && hisp->lo == now.hi)
          songPairs.erase(hisp);

        // connect now.lo with next(now.lo)
        int lo = now.lo;
        auto nxt = alive.lower_bound(now.hi);
        if (nxt == alive.end())
          nxt = alive.begin();
        if (nxt != alive.end())
        {
          int hi = *nxt;
          if (gcd(a[lo], a[hi]) == 1)
          {
            // DEBUG printf("\t\tadding: %d %d\n", lo + 1, hi + 1);
            songPairs.insert(SongPair{lo, hi});
          }
        }
      }
      else if (curr == 0)
        break;
      else
        curr = 0;
    }
    printf("%d", (int)ans.size());
    for (int i: ans)
      printf(" %d", i + 1);
    printf("\n");
  }
  return 0;
}
