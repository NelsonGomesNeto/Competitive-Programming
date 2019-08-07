#include <bits/stdc++.h>
using namespace std;

int main()
{
  int a, b;
  while (scanf("%d %d", &a, &b) && !(!a && !b))
  {
    set<int> acard, bcard; int r;
    for (int i = 0; i < a; i ++)
    {
      scanf("%d", &r);
      acard.insert(r);
    }
    for (int i = 0; i < b; i ++)
    {
      scanf("%d", &r);
      bcard.insert(r);
    }

    int adiff = 0, bdiff = 0;
    for (auto i: acard)
      if (!bcard.count(i))
        adiff ++;
    for (auto i: bcard)
      if (!acard.count(i))
        bdiff ++;

    printf("%d\n", min(adiff, bdiff));
  }
  return(0);
}