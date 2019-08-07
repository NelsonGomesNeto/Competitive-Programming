#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  You have to find x, such that it's the k-th largest number
  Notice that x - 1 is the j-th largest number, and j < k
  
  So, you have to find the largest number x, such that x - 1
  is the j-th number, and j < k

  To do that, you will need to find "j", count the numbers <= x - 1
  We can do that, by counting the contribution of each row
  The i-th row contributes with: min(m, (x - 1) / i)
    Proof: Each row can have at most m numbers, that's the upper bound
    But you want to find how many numbers in that row are <= (x - 1)
      (And remember that each number in this row is a multiple of i)
    (x - 1) / i is a integer division (floor), so:
    ((x - 1) / i) * i is the biggest number <= (x - 1) that is a multiple of i
  So, for each row, you sum min(m, (x - 1) / i), and that is the "j", the
  amount of numbers <= (x - 1)
  BinarySearch it, O(n*lg(n*m)): done
*/

const int maxN = 5e5; lli n, m, k;

lli sum(lli x)
{
  lli s = 0;
  for (int i = 0; i < n; i ++) s += min(m, x / (i + 1));
  return(s);
}

lli binarySearch(lli lo, lli hi)
{
  if (lo >= hi) return(lo);
  lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
  if (sum(mid - 1) < k) return(binarySearch(mid, hi));
  return(binarySearch(lo, mid - 1));
}

int main()
{
  scanf("%lld %lld %lld", &n, &m, &k);

  lli ans = binarySearch(1, n*m);
  printf("%lld\n", ans);

  return(0);
}