#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int emulate(int arr[3], int x)
{
  int t = 0, dist = 0;
  while (t <= x)
  {
    if (arr[0] >= x - t)
    {
      int remT = x - t;
      dist += remT * arr[1];
      break;
    }
    t += arr[0] + arr[2];
    dist += arr[0] * arr[1];
  }
  return dist;
}

int main()
{
  int tak[3], aok[3], x;
  for (int i = 0; i < 3; ++i) scanf("%d", &tak[i]);
  for (int i = 0; i < 3; ++i) scanf("%d", &aok[i]);
  scanf("%d", &x);

  int takDist = emulate(tak, x);
  int aokDist = emulate(aok, x);
  DEBUG printf("%d %d\n", takDist, aokDist);
  printf("%s\n", takDist > aokDist ? "Takahashi" : takDist == aokDist ? "Draw" : "Aoki");

  return 0;
}
