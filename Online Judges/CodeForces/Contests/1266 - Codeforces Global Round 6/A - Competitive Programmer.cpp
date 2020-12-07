#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 418; int n;
char number[101];
int cnt[10];

bool divisibleBy4()
{
  for (int i = 0; i < 100; i += 4)
    if (cnt[i % 10] && cnt[i / 10 % 10] - (i % 10 == i / 10 % 10))
      return true;
  return false;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      memset(cnt, 0, sizeof(cnt));
      scanf("%s", number);
      int sum = 0;
      for (int j = 0; number[j]; j ++)
      {
        cnt[number[j] - '0'] ++;
        sum += number[j] - '0';
      }
      printf("%s\n", sum % 3 == 0 && divisibleBy4() && cnt[0] != 0 ? "red" : "cyan");
    }
  }
  return 0;
}