#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n;
bool valid(lli num)
{
  lli aux = n;
  while (aux > 0 && aux % num == 0) aux /= num;
  return aux % num == 1;
}

int main()
{
  while (scanf("%lld", &n) != EOF)
  {
    set<lli> ans; ans.insert(n);
    for (int i = 2, end = sqrt(n); i <= end; i++)
    {
      if (n % i == 0 && valid(i))
      {
        ans.insert(i);
        if (n % (n / i) == 0 && valid(n / i))
          ans.insert(n / i);
      }
    }
    n--; ans.insert(n);
    for (int i = 2, end = sqrt(n); i <= end; i++)
    {
      if (n % i == 0)
      {
        ans.insert(i);
        if (n % (n / i) == 0)
          ans.insert(n / i);
      }
    }
    ans.erase(0), ans.erase(1);
    // for (int i = 2; i < n; i++)
    //   if (n % i == 1)
    //     ans.insert(i);
    printf("%d\n", (int)ans.size());
    DEBUG {
      for (int i: ans)
        printf("\t%d\n", i);
    }
  }
  return 0;
}