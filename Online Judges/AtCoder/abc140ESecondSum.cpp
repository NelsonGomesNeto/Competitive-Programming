#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The idea is to count the amount lo, hi indexes combinations where number i is the
  second bigger number between it

  We will iterate over the number from n to 1, and keep track of 4 things:
    beforeBigger1: the position of the first number before i
    beforeBigger2: the position of the second number before i
    afterBigger1: the position of the first number after i
    afterBigger2: the position of the second number after i
      Notice that all numbers before or after must be greater than i
        To implement this, use a multiset to store the position of each i
        So, when processing i - 1, you will have the position of all number
        greater than i - 1 inside the multiset, and you know exactly where
        the position of i - 1 lies inside of that.
    There are two possible scenarios (of course, i is the second biggest in both of them):
      The bigger number is before i:
        (beforeBigger1 - beforeBigger2) * (afterBigger1 - pos[i])
        i is the second biggest from beforeBigger1 to beforeBigger2, and from pos[i] to afterBigger1
      The bigger number is after i:
        (afterBigger2 - afterBigger1) * (pos[i] - beforeBigger1)
        i is the second biggest from afterBigger2 to afterBigger1, and from beforeBigger1 to pos[i]
    Now, ans += i * (beforeCombinations + afterCombinations)

  Don't forget to use long long int :)
*/

const int maxN = 1e5; int n;
int p[maxN], pos[maxN + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &p[i]);
      pos[p[i]] = i;
    }

    lli ans = 0;
    multiset<int> abovePosition;
    abovePosition.insert({-1, -1, n, n});
    for (int number = n; number >= 1; number --)
    {
      abovePosition.insert(pos[number]);
      auto it = abovePosition.find(pos[number]);
      int beforeBigger1 = *prev(it, 1), beforeBigger2 = *prev(it, 2);
      int afterBigger1 = *next(it, 1), afterBigger2 = *next(it, 2);
      int beforeCombinations = (beforeBigger1 - beforeBigger2) * (afterBigger1 - pos[number]);
      int afterCombinations = (afterBigger2 - afterBigger1) * (pos[number] - beforeBigger1);
      ans += (lli) number * (beforeCombinations + afterCombinations);
    }
    printf("%lld\n", ans);
  }
  return(0);
}