#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  a[i] + a[j] = a[k], where i < k and j > k

  Store the position of each number, so you can find the position
  of the other number in O(1)

  Suppose you have two arrays (leftLimit and rightLimit), they mean:
    leftLimit[number[i]] is the position of the first number from i to 0
    that is greater then number[i]
    rightLimit[number[i]] is the position of the first number from i to n - 1
    that is greater then number[i]

  for i in [0, n - 1]:
    left slice: i to leftLimit[number[i]]
    right slice: i to rightLimit[number[i]]
    You have two two slices to test, any you choose will give you the same count
    of numbers that can sum to number[i]. So, choose the smaller slice and count

  It may seem to be O(n²), but it's actually O(n*lg)
  Suppose you have the biggest number in the middle of the array, both slices have
  sizes of n / 2, right? Yes, but what about any number beside this biggest number?
  The smaller slice would have size 1. More then that, every number in both slices
  will be limited to a maximum slice of size n / 4, and that goes on for every big
  number.

  You can compute leftLimit and rightLimit arrays using a stack<pair<int, int>>.
  Where the .first is the number and .second is the position of the number.
  stack.push({n + 1, -1}) // The maximum limit will be the beginning
  for i in [0, n - 1]:
    while (s.top().first < number[i]) s.pop()
      Now, you're placed in the first number that is bigger then number[i] :)
    leftLimit[number[i]] = s.top().second
    s.push({number[i], i}) // Next numbers can have number[i] as their limit
  The construction of rightLimit is identical, but from right to left
*/

const int maxN = 2e5; int n;
int a[maxN], numPosition[maxN + 1];
int leftLimit[maxN + 1], rightLimit[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    numPosition[a[i]] = i;
  }
  // for (int i = 0; i < n; i ++) printf("%d%c", a[i], i < n - 1 ? ' ' : '\n');
  stack<pair<int, int>> s; s.push({n + 1, -1});
  for (int i = 0; i < n; i ++)
  {
    while (s.top().first < a[i]) s.pop();
    leftLimit[a[i]] = s.top().second;
    s.push({a[i], i});
  }
  while (!s.empty()) s.pop();
  s.push({n + 1, n});
  for (int i = n - 1; i >= 0; i --)
  {
    while (s.top().first < a[i]) s.pop();
    rightLimit[a[i]] = s.top().second;
    s.push({a[i], i});
  }

  lli ans = 0;
  for (int i = 0; i < n; i ++)
  {
    int lo = leftLimit[a[i]], hi = rightLimit[a[i]];
    if (i - lo < hi - i)
      for (int j = i - 1; j > lo; j --)
        ans += numPosition[a[i] - a[j]] > i && numPosition[a[i] - a[j]] < hi;
    else
      for (int j = i + 1; j < hi; j ++)
        ans += numPosition[a[i] - a[j]] < i && numPosition[a[i] - a[j]] > lo;
  }
  printf("%lld\n", ans);

  return(0);
}