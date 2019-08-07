#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 1e5; int k;
lli n, a[maxK];

lli apSum(lli a1, lli an, lli n)
{
  return(n * (a1 + an) / 2.0);
}

int eval(lli a0)
{
  lli minimumSum = 0, maximumSum = 0;
  for (lli i = 0, lo = a0, hi = a0; i < k; i ++, lo ++)
  {
    minimumSum += lo;
    if (maximumSum + hi < n)
    {
      maximumSum = maximumSum + hi;
      hi *= 2;
    }
    else maximumSum = n;
  }
  if (minimumSum <= n && n <= maximumSum) return(0);
  if (n <= minimumSum) return(1);
  if (n >= maximumSum) return(2);
}

lli binarySearchA0(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = (lo + hi) >> 1;
  int e = eval(mid);
  if (e == 0) return(mid);
  if (e == 1) return(binarySearchA0(lo, mid));
  if (e == 2) return(binarySearchA0(mid + 1, hi));
}

lli binarySearchAi(lli lo, lli hi, int i, lli sum, lli base)
{
  if (lo >= hi) return(lo);
  lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  lli start = mid + 1, end = mid + k - i - 1;
  lli add = apSum(start, end, end - start + 1);
  if (sum + add - (base - mid) > n) return(binarySearchAi(lo, mid - 1, i, sum, base));
  return(binarySearchAi(mid, hi, i, sum, base));
}

int main()
{
  scanf("%lld %d", &n, &k);
  a[0] = binarySearchA0(1, n);
  if (eval(a[0])) printf("NO\n");
  else
  {
    lli sum = a[0]; int i = 0;
    for (i = 1; i < k; i ++)
    {
      a[i] = 2*a[i - 1];
      sum += a[i];
      lli start = a[i] + 1, end = a[i] + k - i - 1;
      lli add = apSum(start, end, end - start + 1);
      if (sum + add >= n) break;
    }
    if (i) a[i] = binarySearchAi(a[i - 1] + 1, a[i], i, sum, a[i]);
    for (i ++; i < k - 1; i ++) a[i] = a[i - 1] + 1;
    sum = 0; for (i = 0; i < k - 1; i ++) sum += a[i];
    a[k - 1] = n - sum;
    printf("YES\n");
    for (int i = 0; i < k; i ++) printf("%lld ", a[i]); printf("\n");
  }

  return(0);
}