#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n; scanf("%d", &n);
    vector<int> number(n), even, odd;
    for (int i = 0; i < n; i ++)
    {
      scanf("%1d", &number[i]);
      if (number[i] & 1)
        odd.push_back(number[i]);
      else if (number[i] != 0)
        even.push_back(number[i]);
    }
    reverse(odd.begin(), odd.end());
    reverse(even.begin(), even.end());

    vector<int> ans;
    if (odd.empty())
      printf("-1\n");
    else
    {
      if (odd.size() > 1)
        printf("%d%d\n", odd[1], odd[0]);
      else
        printf("-1\n");
    }
  }
  return 0;
}
