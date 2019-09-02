#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e3; int n;
lli a[maxN];
map<lli, int> numbers;

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    numbers.clear();

    int ans = n - 1;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      if (!numbers.count(a[i]))
        numbers[a[i]] = 0;
      numbers[a[i]] ++;
    }
    int problematic = 0;
    for (auto i: numbers)
      if (i.second > 1)
        problematic ++;

    if (problematic == 0)
      ans = 0;
    else
      for (int i = 0; i < n; i ++)
      {
        int solved = 0;
        for (int j = i; j < n; j ++)
        {
          if (numbers[a[j]] -- == 2)
            solved ++;
          if (solved == problematic)
            ans = min(ans, j - i + 1);
        }
        for (int j = i; j < n; j ++)
          numbers[a[j]] ++;
      }
    printf("%d\n", ans);
  }

  return(0);
}
