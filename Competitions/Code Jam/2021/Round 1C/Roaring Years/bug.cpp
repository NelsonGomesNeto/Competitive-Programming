#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

vector<int> getDigits(lli aux)
{
  vector<int> digits;
  while (aux)
  {
    digits.push_back(aux % 10);
    aux /= 10;
  }
  reverse(digits.begin(), digits.end());
  return digits;
}

bool roaring(lli y)
{
  vector<int> digits = getDigits(y);

  for (int i = 0; i < digits.size(); i++)
  {
    lli num = 0;
    for (int j = 0; j <= i; j++)
      num = num*10LL + digits[j];
    DEBUG printf("\t%lld - %lld\n", y, num);

    int at = i + 1;
    if (at == digits.size())
      continue;

    bool valid = true;
    while (at < digits.size())
    {
      num++;
      vector<int> now = getDigits(num);
      if (at + now.size() > digits.size())
      {
        valid = false;
        break;
      }

      for (int j = 0; j < now.size(); j++)
        if (digits[at + j] != now[j])
        {
          valid = false;
          break;
        }

      at += now.size();
    }

    if (valid && at == digits.size())
      return true;
  }
  return false;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli y; scanf("%lld", &y);
    y++;
    while (!roaring(y))
      y++;

    printf("Case #%d: %lld\n", tt, y);
  }
  return 0;
}