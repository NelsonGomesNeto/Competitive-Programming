#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e5;
const int maxMasks = 1 << 10;
const int allMask = maxMasks - 1;
char ss[maxN + 1];
vector<int> s;

int isEven[maxN + 1];
lli maskCount[maxMasks];

string getBinary(int num)
{
  string a;
  while (num)
  {
    a.push_back('0' + (num & 1));
    num >>= 1;
  }
  reverse(a.begin(), a.end());
  return a;
}

int main()
{
  while (~scanf(" %s", ss))
  {
    s.clear();
    for (int i = 0; ss[i]; ++i)
      s.push_back(ss[i] - '0');

    isEven[0] = allMask;
    for (int i = 0; i < s.size(); ++i)
      isEven[i + 1] = isEven[i] ^ (1 << s[i]);

    fill(maskCount, maskCount + maxMasks + 1, 0);
    for (int i = 1; i < s.size() + 1; ++i)
      ++maskCount[isEven[i]];

    lli ans = maskCount[allMask];
    int curr = allMask;
    for (int i = 0; i < s.size(); ++i)
    {
      --maskCount[isEven[i + 1]];
      curr ^= 1 << s[i];
      DEBUG printf("\t%d %s %lld\n", i, getBinary(curr).c_str(), maskCount[curr]);
      ans += maskCount[curr];
    }

    printf("%lld\n", ans);
  }
  return 0;
}
