#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli k, d, t;

int main()
{
  scanf("%lld %lld %lld", &k, &d, &t);
  t *= 2; // To simplify calculations, make t = 2t

  lli period = (k / d + (k % d > 0)) * d; // The first time when she will get to the stove off
  
  lli cookingPerPeriod = 2*k + (period - k);
  // Since t = 2t, stove on will account for 2k and of won't need to divide by 2

  lli wholePeriods = t / cookingPerPeriod;
  // To know how many times we can just apply the period and jump to the end
  lli cookingTime = wholePeriods * cookingPerPeriod;
  // These will account for (wholePeriods * cookingPerPeriod) cooking time
  // And (wholePeriods * period) actual time

  lli left = t - cookingTime;
  // But there may be some time left that can't be covered by a period

  double totalTime;
  if (left <= 2*k)
  {
    // Will finish with the stove on
    totalTime = wholePeriods * period + left / 2.0;
    // So, the time left will be 2 times faster, since the stove is on
  }
  else
  {
    // will finish with the stove off
    totalTime = wholePeriods * period + k + (left - 2*k);
    // So, add k, which is the time the stove will be on
    // And, add (left - 2*k), which is the time the stove will be off
  }

  printf("%lf\n", totalTime);

  return(0);
}