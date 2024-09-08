#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int mh, mm;
int h, m;

bool flippable[11] = {
  true,
  true,
  true,
  false,
  false, 
  true,
  false,
  false,
  true,
  false
};
int flipTable[11] = {
  0,
  1,
  5,
  -1,
  -1, 
  2,
  -1,
  -1,
  8,
  -1
};

bool can(int num)
{
  while (num)
  {
    if (!flippable[num % 10])
      return false;
    num /= 10;
  }
  return true;
}
bool canFlip()
{
  if (!(can(h) && can(m)))
    return false;

  int newH = flipTable[m % 10]*10 + flipTable[m / 10];
  int newM = flipTable[h % 10]*10 + flipTable[h / 10];

  return newH < mh && newM < mm;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    
    scanf("%d %d", &mh, &mm);
    scanf("%d:%d", &h, &m);

    while (!canFlip())
    {
      m++;
      if (m == mm)
        h++, m = 0;
      if (h == mh)
        h = 0;
    }
    printf("%02d:%02d\n", h, m);
  }
  return 0;
}
