#include <bits/stdc++.h>
using namespace std;

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    int number; scanf("%d", &number); bool done = false;
    if (number < 4 || ((number & 1) && number <= 11 && number != 9)) printf("-1\n");
    else if (number & 1) printf("%d\n", 1 + ((number-9) % 4 != 0) + (number - 9 - 6*((number-9) % 4 != 0)) / 4);
    else printf("%d\n", (number % 4 != 0) + (number - 6*(number % 4 != 0)) / 4);
  }
  return(0);
}
// 4 6 9