#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxW = 1e5; int w; lli n;
lli x[maxW];

lli leftTotal, rightTotal;
lli l[maxW + 1], r[maxW + 1];
vector<lli> trial;
vector<pair<lli, lli>> rights, lefts;

lli rcalc(lli a, lli b)
{
  if (b >= a) return b - a;
  return b + n - a;
}
lli lcalc(lli a, lli b)
{
  // return rcalc(b, a);
  if (b <= a) return a - b;
  return n - b + a;
}

lli ans;
void solve()
{
  sort(x, x+w);

  trial.clear();
  for (int i = 0; i < w; i++)
    trial.push_back(x[i]);
  trial.resize(distance(trial.begin(), unique(trial.begin(), trial.end())));

  lefts.clear(), rights.clear();
  for (int i = 0; i < w; i++)
  {
    lli ld = lcalc(*trial.begin(), x[i]);
    lli rd = rcalc(*trial.begin(), x[i]);
    if (ld <= rd) lefts.push_back({ld, x[i]});
    else rights.push_back({rd, x[i]});
  }
  sort(lefts.begin(), lefts.end());
  sort(rights.begin(), rights.end());

  l[0] = 0;
  for (int i = 0; i < lefts.size(); i++)
    l[i + 1] = l[i] + lefts[i].first;
  r[0] = 0;
  for (int i = 0; i < rights.size(); i++)
    r[i + 1] = r[i] + rights[i].first;

  leftTotal = l[lefts.size()], rightTotal = r[rights.size()];

  ans = min(ans, leftTotal + rightTotal);
  int li = lefts.size() - 1, ri = 0; lli delta = 0;
  lli rightToLeftCount = 0, leftToRightCount = 0;
  lli rlDelta = 0, lrDelta = 0;
  /*
    0 3 3 6 7
  */
  for (int i = 1; i < trial.size(); i++)
  {
    DEBUG printf("%lld %lld | %lld | %lld\n", trial[0], trial[i], trial[i] - trial[0], n >> 1LL);
    if (trial[i] - trial[0] >= (n >> 1)) break;
    lli d = trial[i] - trial[i - 1];
    delta += d;
    DEBUG printf("\t%lld counts: %lld %lld\n", trial[i], rightToLeftCount, leftToRightCount);
    rlDelta += rightToLeftCount * d;
    lrDelta -= leftToRightCount * d;
    while (ri < rights.size() && lcalc(trial[i], rights[ri].second) <= rcalc(trial[i], rights[ri].second))
    {
      rlDelta += lcalc(trial[i], rights[ri].second);
      ri++;
      rightToLeftCount++;
    }
    while (li >= 0 && rcalc(trial[i], lefts[li].second) <= lcalc(trial[i], lefts[li].second))
    {
      lrDelta += rcalc(trial[i], lefts[li].second);
      li--;
      leftToRightCount++;
    }
    DEBUG printf("\t%lld %lld - %lld %lld\n", rightToLeftCount, rlDelta, leftToRightCount, lrDelta);

    lli rt = rightTotal - r[ri] - delta * ((int)rights.size() - ri) + lrDelta;
    lli lt = l[li + 1] + delta * (li + 1) + rlDelta;
    DEBUG printf("\t\t%lld - %lld %lld - %lld\n", trial[i], lt, rt, rt + lt);
    ans = min(ans, rt + lt);
  }
  DEBUG printf("----\n");
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &w, &n);
    for (int i = 0; i < w; i++)
    {
      scanf("%lld", &x[i]);
      x[i]--;
    }

    ans = 1e18;
    solve();
    for (int i = 0; i < w; i++)
      x[i] = n - x[i] - 1;
    solve();

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}