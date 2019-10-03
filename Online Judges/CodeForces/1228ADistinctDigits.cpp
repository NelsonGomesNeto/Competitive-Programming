#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

bool valid(int num)
{
  int cnt[10]; memset(cnt, 0, sizeof(cnt));
  while (num)
  {
    cnt[num % 10] ++;
    if (cnt[num % 10] > 1) return false;
    num /= 10;
  }
  return true;
}

int main()
{
  int l, r; scanf("%d %d", &l, &r);
  int x;
  for (x = l; x <= r; x ++)
    if (valid(x))
      break;
  printf("%d\n", x > r ? -1 : x);
  return 0;
}
