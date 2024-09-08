#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
char s[maxN + 1];
map<int, int> cnt;

int main()
{
  while (scanf(" %s", s) != EOF)
  {
    cnt.clear();
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
      int val = s[i] - '0';
      if (!cnt.count(val))
        cnt[val] = 0;
      cnt[val]++;
    }

    if (n == 1)
      printf("%s\n", s[0] == '8' ? "Yes" : "No");
    else if (n == 2)
    {
      int a = s[0] - '0', b = s[1] - '0';
      bool is = (10*a + b) % 8 == 0 || (10*b + a) % 8 == 0;
      printf("%s\n", is ? "Yes" : "No");
    }
    else
    {
      /*
      The last three digits are divisible by 8.

      Add four times the hundreds digit to twice the tens digit to the ones digit. The result must be divisible by 8.
      */
      vector<int> digits;
      for (auto i: cnt)
        for (int j = 0; j < min(i.second, 3); j++)
          digits.push_back(i.first);

      bool can = false;
      for (int i = 0; i < digits.size(); i++)
        for (int j = i + 1; j < digits.size(); j++)
          for (int k = j + 1; k < digits.size(); k++)
          {
            vector<int> hehe = {digits[i], digits[j], digits[k]};
            sort(hehe.begin(), hehe.end());
            do
            {
              int num = hehe[0]*4 + hehe[1]*2 + hehe[2];
              if (num % 8 == 0)
                can = true;
            } while (next_permutation(hehe.begin(), hehe.end()));
          }
      printf("%s\n", can ? "Yes" : "No");
    }
  }
  return 0;
}