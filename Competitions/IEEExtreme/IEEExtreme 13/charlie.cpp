#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10, maxK = 100; int n;
const lli inf = 1e15;
lli budget;
int k[maxN];
lli smallSum[maxN], bigSum[maxN];
vector<lli> options[maxN];

lli valid[maxN];
int cutpoint = 0;
vector<lli> lo, hi;
void solve(int dir = 1, int i = 0, lli b = budget, lli now = 0)
{
  if (i == cutpoint + (dir == 1))
  {
    if (dir == 1) lo.push_back(now);
    else hi.push_back(now);
    return;
  }

  for (int j = 0; j < options[i].size(); j ++)
    if (b - options[i][j] >= 0)
      solve(dir, i + dir, b - options[i][j], now + options[i][j]);
}

void printArray(vector<lli> arr)
{
  printf("%d\n", (int) arr.size());
  for (int i = 0; i < arr.size(); i ++)
    printf("%lld%c", arr[i], i < arr.size() - 1 ? ' ' : '\n');
}

lli binarySearch(lli target)
{
  int l = 0, h = hi.size() - 1;
  while (l < h)
  {
    int mid = (l + h + 1) >> 1;
    if (hi[mid] > target) h = mid - 1;
    else l = mid; 
  }
  return hi[l] > target ? -1 : hi[l];
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    lo.clear(), hi.clear();
    memset(valid, 0, sizeof(valid));
    scanf("%lld %d", &budget, &n);
    int s = 0;
    for (int i = 0; i < n; i ++)
    {
      options[i].clear();
      scanf("%d", &k[i]);
      s += k[i];
    }
    int now = 0;
    for (int i = 0; i < n; i ++)
    {
      now += k[i];
      if (now >= (s >> 1))
      {
        cutpoint = i;
        break;
      }
    }

    lli sum = 0, maxSum = 0;
    for (int i = 0; i < n; i ++)
    {
      lli minimum = inf, maximum = -inf;
      for (int j = 0; j < k[i]; j ++)
      {
        lli c; scanf("%lld", &c);
        options[i].push_back(c), minimum = min(minimum, c), maximum = max(maximum, c);
      }
      // sort(options[i].begin(), options[i].end(), greater<lli>());
      sum += minimum, maxSum += maximum;
      smallSum[i] = sum, bigSum[i] = maxSum;
    }
    // sort(options, options+n, greater<vector<lli>>());

    lli ans = 0;
    if (sum >= budget)
      ans = sum == budget ? sum: 0;
    else
    {
      // printf("cutpoint %d\n", cutpoint);
      solve(1, 0);
      solve(-1, n - 1);
      sort(lo.begin(), lo.end());
      sort(hi.begin(), hi.end());
      DEBUG printArray(lo);
      DEBUG printArray(hi);
      for (int i = 0; i < lo.size(); i ++)
      {
        lli other = binarySearch(budget - lo[i]);
        DEBUG printf("%lld %lld %lld\n", lo[i], budget - lo[i], other);
        if (other != -1)
          ans = max(ans, lo[i] + other);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}