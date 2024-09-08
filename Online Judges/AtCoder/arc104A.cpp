#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b;
  while (scanf("%d %d", &a, &b) != EOF)
  {
    int x, y; bool done = false;
    for (x = -300; x <= 300 && !done; x+=!done)
      for (y = -300; y <= 300 && !done; y+=!done)
        if (x + y == a && x - y == b)
          done = true;
    printf("%d %d\n", x, y);
  }
  return 0;
}