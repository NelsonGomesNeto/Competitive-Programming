#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Ideas:
  Dijkstra didn't work because two drivers can reach the same cluster at the same time
  and I couldn't figure out a way to confirm that either choice is better

  But I've got another idea:
    driver1 cluster1 driver2 cluster2
      Notice that it's not that likely that this will always be the case
      but it's easier to understand the idea looking at this case
    The left most cluster *will* be exploded, we just need to choose which driver will do it
    The left most driver probably is the best, because it will leave driver2 free to go to
    cluster2 and driver1 may stop working from there on
    Through a binary search, we will test with a time limit, if dist(driver1, cluster1) <= time limit
    We it's better to just move it there and get over with it

    The problem here is that when the driver is at the right, it might be better to just make it get as many
    clusters as possible to the right before going to the left to kill this left most cluster
    It might also be better to make it go right and then left, so figure out a way to handle that
*/

const int maxN = 1e6; int n, m, k, s;
const lli inf = 1e9;
lli p[maxN], q[maxN];
lli ap, bp, cp, dp;
lli aq, bq, cq, dq;

map<lli, lli> drivers;
set<lli> clusters;

bool worthIt(lli left, lli right, lli timeLimit)
{
  lli at = drivers.begin()->first, baseTime = drivers.begin()->second;
  return min(abs(at - left), abs(right - at)) + abs(right - left) + baseTime <= timeLimit;
}

void moveLeftMostDriver(lli newPos, lli newTime)
{
  drivers.erase(drivers.begin());
  if (!drivers.count(newPos))
    drivers[newPos] = inf;
  drivers[newPos] = min(drivers[newPos], newTime);
}

bool can(lli timeLimit)
{
  drivers.clear(), clusters.clear();
  for (int i = 0; i < n; i++) drivers[p[i]] = 0;
  for (int i = 0; i < m; i++) clusters.insert(q[i]);

  while (!clusters.empty())
  {
    while (!drivers.empty() && abs(*clusters.begin() - drivers.begin()->first) + drivers.begin()->second > timeLimit)
      drivers.erase(drivers.begin());
    if (drivers.empty() && !clusters.empty())
      return false;
    
    lli driverPos = drivers.begin()->first, currentTime = drivers.begin()->second, leftMostCluster = *clusters.begin();

    auto rightCluster = clusters.lower_bound(driverPos);
    if (rightCluster != clusters.end())
      while (next(rightCluster) != clusters.end() && worthIt(leftMostCluster, *next(rightCluster), timeLimit))
        rightCluster++;

    if (rightCluster != clusters.end() && worthIt(leftMostCluster, *rightCluster, timeLimit))
    {
      if (abs(driverPos - leftMostCluster) < abs(*rightCluster - driverPos))
        moveLeftMostDriver(leftMostCluster, abs(*rightCluster - driverPos) + abs(*rightCluster - leftMostCluster) + currentTime);
      else
        moveLeftMostDriver(*rightCluster, abs(driverPos - leftMostCluster) + abs(*rightCluster - leftMostCluster) + currentTime);

      while (clusters.begin() != rightCluster)
        clusters.erase(clusters.begin());
      clusters.erase(clusters.begin());
    }
    else
    {
      moveLeftMostDriver(leftMostCluster, abs(leftMostCluster - driverPos) + currentTime);

      while (!clusters.empty() && *clusters.begin() <= driverPos)
        clusters.erase(clusters.begin());
    }
  }
  return true;
}

lli binarySearch()
{
  lli lo = 0, hi = 1e9;
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1LL;
    if (can(mid)) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d %d %d", &n, &m, &k, &s);
    for (int i = 0; i < k; i++) scanf("%lld", &p[i]);
    scanf("%lld %lld %lld %lld", &ap, &bp, &cp, &dp);
    for (int i = k; i < n; i++) p[i] = ((ap * p[i - 2] + bp * p[i - 1] + cp) % dp) + 1;

    for (int i = 0; i < k; i++) scanf("%lld", &q[i]);
    scanf("%lld %lld %lld %lld", &aq, &bq, &cq, &dq);
    for (int i = k; i < m; i++) q[i] = ((aq * q[i - 2] + bq * q[i - 1] + cq) % dq) + 1;

    // sort(p, p+n);
    // sort(q, q+m);
    DEBUG {
      printf("P: "); for (int i = 0; i < n; i++) printf("%lld%c", p[i], i < n - 1 ? ' ' : '\n');
      printf("Q: "); for (int i = 0; i < m; i++) printf("%lld%c", q[i], i < m - 1 ? ' ' : '\n');
    }

    lli ans = binarySearch();

    printf("Case #%d: %lld\n", tt, ans); fflush(stdout);
    DEBUG printf("\n");
  }
  return 0;
}