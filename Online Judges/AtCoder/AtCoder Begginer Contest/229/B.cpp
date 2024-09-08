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
  return digits;
}

int main()
{
  lli a, b;
  while (~scanf("%lld %lld", &a, &b))
  {
    vector<int> ad = getDigits(a);
    vector<int> bd = getDigits(b);

    if (ad.size() < bd.size()) swap(ad, bd);

    while (bd.size() < ad.size())
      bd.push_back(0);
    assert(ad.size() == bd.size());

    bool hard = false;
    for (int i = 0; i < ad.size(); i++)
    {
      DEBUG printf("\t%d %d\n", ad[i], bd[i]);
      if (ad[i] + bd[i] >= 10)
        hard = true;
    }
    printf("%s\n", hard ? "Hard" : "Easy");
  }
  return 0;
}
