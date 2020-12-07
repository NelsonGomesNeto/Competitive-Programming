#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;

struct Segment
{
  lli x; bool isLeft; int index;
  bool operator<(const Segment &other) const { return x < other.x || (x == other.x && isLeft > other.isLeft); }
};
vector<Segment> segments;
int cnt[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    segments.clear();
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      lli l, r; scanf("%lld %lld", &l, &r);
      segments.push_back({l, true, i}), segments.push_back({r, false, i});
      cnt[i] = 0;
    }
    sort(segments.begin(), segments.end());

    int ans = 0;
    set<int> now;
    for (Segment &s: segments)
    {
      if (s.isLeft)
        now.insert(s.index);
      else
      {
        now.erase(s.index);
        if (now.empty())
          ans ++, cnt[s.index] --;
        if (now.size() == 1)
          cnt[*now.begin()] ++;
      }
    }

    int bestDiff = -1;
    for (int i = 0; i < n; i ++)
      bestDiff = max(bestDiff, cnt[i]);

    printf("%d\n", ans + bestDiff);
  }
  return 0;
}
