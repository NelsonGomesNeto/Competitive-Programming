#include <bits/stdc++.h>
#define ull unsigned long long int
#define lli long long int
using namespace std;

/* Tutorial:
  This is a very interesting digit DP problem:
  You will binary search for the floor in which the count of valid floors
  below is equal to n

  To count the valid floors below a given x:
    The naive way is to simply test every number below or equal to x and count
    the valid ones
    But there's a smarter way to do this: with digit DP
  You can construct every number below or equal to, from left to right, by choosing
  each digit (and not allowing invalid numbers to happen)
  The states are identified by: digit, isSmaller, prevIsOne
    digit - keeps track of which digit you're trying to fill
    isSmaller - if previously was chosen a digit that is smaller than in x
    prevIsOne - if the previous chosen digit was 1
  So, for each digit: try to fill it with every possible digit and use memoization
*/

lli n;
lli memo[20][2][2], number[20], numberSize;
lli solve(int digit = 0, bool smaller = false, bool prevIsOne = false)
{
  if (digit == numberSize) return(1);
  if (memo[digit][smaller][prevIsOne] == -1)
  {
    lli ans = 0;
    for (int i = 0; i <= 9; i ++)
    {
      if (!smaller && i > number[digit]) break;
      if (i == 4 || (i == 3 && prevIsOne)) continue;
      ans += solve(digit + 1, smaller || i < number[digit], i == 1);
    }
    memo[digit][smaller][prevIsOne] = ans;
  }
  return(memo[digit][smaller][prevIsOne]);
}

void fillNumber(ull num)
{
  numberSize = 0;
  while (num)
  {
    number[numberSize ++] = num % 10;
    num /= 10;
  }
  reverse(number, number+numberSize);
}

ull binarySearch(ull lo = 0, ull hi = ULONG_LONG_MAX)
{
  while (lo < hi)
  {
    ull mid = lo + (hi - lo) / 2ull;
    fillNumber(mid), memset(memo, -1, sizeof(memo));
    // - 1 because only zeros isn't a valid floor
    if (solve() - 1 >= n) hi = mid;
    else lo = mid + 1;
  }
  return(lo);
}

int main()
{
  while (scanf("%lld", &n) != EOF && n)
    printf("%llu\n", binarySearch(n));
  return(0);
}