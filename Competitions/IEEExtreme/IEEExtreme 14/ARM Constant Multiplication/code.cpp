#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 0; tt < t; tt++)
    {
      // if (tt) printf("MOV R0, R2, LSL #0\n");

      lli c; scanf("%lld", &c);
      if (c <= 1)
      { 
        if (c == 1) printf("MOV R0, R1, LSL #0\n");
      }
      else if (__builtin_popcount(c) == 1) // power of two
      {
        int p = 0;
        while ((1LL << p) != c) p++;
        printf("MOV R0, R0, LSL #%d\n", p);
      }
      else if (__builtin_popcount(c - 1) == 1) // power of two
      {
        int p = 0;
        while ((1LL << p) != c - 1) p++;
        printf("ADD R0, R0, R0, LSL #%d\n", p);
      }
      else
      {
        lli target = c - 1;
        bool first = true;
        for (int i = 0; i < 32; i++)
          if (target & (1LL << i))
          {
            printf("ADD R1, R1, R0, LSL #%d\n", i);
            first = false;
          }
        printf("ADD R0, R1, R0, LSL #0\n");
      }

      printf("END\n");
    }
  }
  return 0;
}