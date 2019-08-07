#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int inf = 1000;
bool ans[181];

int main()
{
  ans[0] = true;
  int h = 0, m = 0;
  while (h <= 5*12)
  {
    m = (m + 1) % 60;
    if (m % 12 == 0) h ++;
    int angle = min(6*(m - h) * (m - h < 0 ? -inf : 1), 6*(60 - h + m) * (60 - h + m < 0 ? -inf : 1));
    // printf("%d -- %d %d\n", angle, m, h);
    ans[angle] = true;
  }
  int degree;
  while (scanf("%d", &degree) != EOF)
    printf("%c\n", degree % 6 == 0 ? 'Y' : 'N');

  return(0);
}