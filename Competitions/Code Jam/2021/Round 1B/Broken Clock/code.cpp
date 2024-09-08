#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  You will have to try any permutation of a, b and c
*/

const lli mod = 360LL * 12 * 1e10;
const lli nanoSec = 1000000000LL;

int main()
{
  int hehe = 0;
  int t;
  while (~scanf("%d", &t))
  {
    if (hehe++) printf("-------\n");
    for (int tt = 1; tt <= t; tt++)
    {
      vector<lli> abc(3);
      for (int i = 0; i < 3; i++) scanf("%lld", &abc[i]);
      sort(abc.begin(), abc.end());

      vector<lli> ans(4, -1);
      // hour - 1 tick per nanosecond
      // minute - 12 ticks per nanosecond
      // second - 720 ticks per nanosecond
      do
      {
        if (ans[0] != -1) break;

        // nanoseconds
        for (int i = 0; i < 720 * 2; i++)
        {
          // abc[0] - hours
          // abc[1] - minutes
          // abc[2] - seconds

          // totalMinutes ticks = hour * 12
          // totalSeconds ticks = hour * 720

          lli hourTicks = abc[0] + i;

          lli totalMinutes = hourTicks * 12;
          lli totalSeconds = hourTicks * 720;
          lli angleMinutes = totalMinutes % mod;
          lli angleSeconds = totalSeconds % mod;
          if (angleMinutes == abc[1] + i && angleSeconds == abc[2] + i)
          {
            ans[0] = hourTicks / (mod / 12);
            ans[1] = angleMinutes / (mod / 60);
            ans[2] = angleSeconds / (mod / 60);
            ans[3] = i;
            break;
          }

          // seconds
          for (int j = 0; j < 360 * 12; j++)
          {
            // abc[0] - hours
            // abc[1] - minutes
            // abc[2] - seconds

            // totalMinutes ticks = hour * 12
            // totalSeconds ticks = hour * 720

            lli addNanoSeconds = nanoSec * 60 * j + i;
            lli hourTicks = (abc[0] + addNanoSeconds) % mod;

            lli totalMinutes = hourTicks * 12;
            lli totalSeconds = hourTicks * 720;
            lli angleMinutes = totalMinutes % mod;
            lli angleSeconds = totalSeconds % mod;
            if (angleMinutes == (abc[1] + addNanoSeconds) % mod && angleSeconds == (abc[2] + addNanoSeconds) % mod)
            {
              ans[0] = hourTicks / (mod / 12);
              ans[1] = angleMinutes / (mod / 60);
              ans[2] = angleSeconds / (mod / 60);
              ans[3] = 0;
              DEBUG printf("\tCase #%d: %lld %lld %lld %lld\n", tt, ans[0], ans[1], ans[2], ans[3]);
              break;
            }
          }
        }
      }
      while (next_permutation(abc.begin(), abc.end()));

      printf("Case #%d: %lld %lld %lld %lld\n", tt, ans[0], ans[1], ans[2], ans[3]);
      fflush(stdout);
      assert(ans[0] != -1);
    }
  }
  return 0;
}
/*
1 - 1/12*10^-10
x - 360
x = 360 / 
*/