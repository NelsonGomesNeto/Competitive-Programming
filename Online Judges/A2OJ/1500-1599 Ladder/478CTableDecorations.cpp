#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli ballons[3];

int main()
{
  scanf("%lld %lld %lld", &ballons[0], &ballons[1], &ballons[2]);
  sort(ballons, ballons+3);
  printf("%lld\n", min((ballons[0] + ballons[1] + ballons[2]) / 3, ballons[0] + ballons[1]));

  return(0);
}