#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli apSum(lli a1, lli an)
{
  lli n = abs(an - a1) + 1LL;
  // printf("apSum: %lld %lld %lld\n", a1, an, n);
  return n * (a1 + an) >> 1LL;
}

struct Interval
{
  int lo, hi, vlo, vhi;
  void print() { printf("%d %d - %d %d\n", lo, hi, vlo, vhi); }
  lli getSum(int i, int j)
  {
    i = max(i, lo), j = min(j, hi);
    if (vlo < vhi)
      return apSum(vlo + (i - lo), vhi - (hi - j));
    else
      return apSum(vlo - (i - lo), vhi + (hi - j));
  }
  void replaceBy(const Interval &other) { *this = other; }
  void reverse() { swap(vlo, vhi); }
  pair<Interval, Interval> cutAt(int i)
  {
    return pair<Interval, Interval>{
      Interval{lo, i - 1, vlo, vlo < vhi ? vlo + (i - 1 - lo) : vlo - (i - 1 - lo)},
      Interval{i, hi, vlo < vhi ? vlo + (i - lo) : vlo - (i - lo), vhi}
    };
  }
};
list<Interval> intervals;
int n, m;

int main()
{
  scanf("%d %d", &n, &m);

  intervals.push_back(Interval{1, n, 1, n});
  for (int i = 0; i < m; i ++)
  {
    char op; int lo, hi; scanf(" %c %d %d", &op, &lo, &hi);
    if (op == 'S')
    {
      list<Interval>::iterator it = intervals.begin();
      while (it->hi < lo) it ++;
      // printf("S - %d %d\n", lo, hi);

      lli ans = 0;
      for (; it != intervals.end() && it->lo <= hi; it ++)
        ans += it->getSum(lo, hi);
      printf("%lld\n", ans);
    }
    else
    {
      // printf("I - %d %d\n", lo, hi);
      list<Interval>::iterator it = intervals.begin();
      while (it->hi < lo) it ++;
      list<Interval>::iterator loit = it, hiit;

      if (it->lo < lo)
      {
        pair<Interval, Interval> splitted = it->cutAt(lo);
        intervals.insert(it, splitted.first);
        it->replaceBy(splitted.second);
      }

      for (; it != intervals.end() && it->lo <= hi; it ++)
      {
        if (it->hi > hi)
        {
          pair<Interval, Interval> splitted = it->cutAt(hi + 1);
          splitted.first.reverse();
          hiit = intervals.insert(it, splitted.first);
          it->replaceBy(splitted.second);
          break;
        }
        it->reverse();
        hiit = it;
      }

      reverse(loit, ++hiit);
      loit = intervals.begin();
      // Relabeling after reversion
      for (int i = 1; loit != hiit; loit ++)
      {
        int diff = loit->hi - loit->lo;
        loit->lo = i, loit->hi = i + diff;
        i = loit->hi + 1;
      }
    }

    // printf("--------\nIntervals:\n");
    // for (auto &i: intervals) i.print();
    // printf("--------\n");
  }

  return(0);
}