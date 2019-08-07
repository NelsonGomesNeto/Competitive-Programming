#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define DEBUG if(0)

lli apSum(lli a, lli b)
{
  // lli sum = 0;
  // for (lli i = a; i <= b; i ++)
  //   sum += i;
  // return(sum);
  return((double)(a+b)/2.0*(b - a + 1));
}

int main()
{
  lli n, k; scanf("%lld %lld", &n, &k);
  char workout[n + 100]; scanf("\n%s", workout);
  vector<lli> seq;
  lli total = 0;
  for (lli i = 0; i < n;)
  {
    while (i < n && workout[i] == '0') i ++;
    lli dx = 0, acc = 0;
    while (i < n && workout[i] == '1')
    {
      dx ++;
      acc += dx;
      i ++;
    }
    total += acc;
    seq.push_back(dx);
  }

  sort(seq.begin(), seq.end());
  lli at = seq.size() - 1, removed = 0;
  while (total > k)
  {
    total -= apSum(0, seq[at]);
    lli news = seq[at] / 2 - !(seq[at] & 1);
    DEBUG printf("from %lld %lld to %lld %lld end %lld\n", seq[at], apSum(0, seq[at]), news, seq[at] / 2, apSum(0, news) + apSum(0, seq[at] / 2));
    if (news >= 0) total += apSum(0, news);
    total += apSum(0, seq[at] / 2);
    seq[at] /= 2;
    seq.push_back(news);
    sort(seq.begin(), seq.end());
    removed ++;
    at ++;
  }
  printf("%lld\n", removed);

  return(0);
}