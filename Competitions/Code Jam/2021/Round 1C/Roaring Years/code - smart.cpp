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

vector<lli> roaring(lli y)
{
  vector<lli> possibles;
  vector<int> digits = getDigits(y);

  for (int i = 0; i < digits.size(); i++)
  {
    lli num = 0, base;
    for (int j = 0; j <= i; j++)
      num = num*10LL + digits[j];
    base = num;
    int baseDigits = getDigits(base).size();
    for (int k = 0; k <= 100; k++)
    {
      if (getDigits(num).size() > baseDigits) break;

      DEBUG printf("\t%lld - %lld\n", y, num);

      int at = i + 1;
      if (at == digits.size())
        continue;

      bool valid = true;
      vector<vector<int>> hehe;
      hehe.push_back(getDigits(num));
      lli curr = num;
      while (at < digits.size())
      {
        curr++;
        vector<int> now = getDigits(curr);
        if (at + now.size() > digits.size())
        {
          valid = false;
          break;
        }
        hehe.push_back(now);

        at += now.size();
      }

      if (valid && at == digits.size())
      {
        DEBUG printf("\tvalid %lld\n", num);
        lli curr = 0;
        for (int i = 0; i < hehe.size(); i++)
          for (int j = 0; j < hehe[i].size(); j++)
            curr = curr*10 + hehe[i][j];
        possibles.push_back(curr);
      }

      num++;
    }
  }
  return possibles;
}

bool check(lli y)
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

    vector<lli> possibles = roaring(y + 1);
    lli ans = LONG_LONG_MAX;
    for (lli p: possibles)
      if (p > y)
        ans = min(ans, p);

    if (ans == LONG_LONG_MAX)
    {
      y++;
      while (!check(y))
        y++;
      ans = y;
    }

    printf("Case #%d: %lld\n", tt, ans);
  }
  return 0;
}