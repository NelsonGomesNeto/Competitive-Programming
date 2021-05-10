#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400; int n; lli m;
lli memo[maxN + 1][maxN + 1];

/* The opposite idea (turning off computers instead of turning them on)
  Here the rules are that if a computer is on alone: it will shutdown automatically

  So you start with n computers on and forming a single segment
  And will turn them off (which will create new segments)
  Your target is to have 0 computers on (and 0 segments)
*/
lli solve(int on = n, int seg = 1)
{
  if (on < 0 || seg < 0) return 0;
  if (on == 0) return seg == 0;

  lli &ans = memo[on][seg];
  if (ans != -1) return ans;
  ans = 0;

  // Turn off the computer on the border of a segment
  ans = (ans + 2LL * seg * solve(on - 1, seg) % m) % m;
  // Turn off two computers on the border of a segment (by turning off the one before the last)
  ans = (ans + 2LL * seg * solve(on - 2, seg) % m) % m;

  // Turning off a segment
  ans = (ans + seg * solve(on - 1, seg - 1) % m) % m;

  // Two segments merge will only happen through a automatic turn on!
  // So you will have to turn off 2 or 3 computers

  // Turn off a computer from a segment (splitting a segment into two)
  ans = (ans + 2LL * seg * solve(on - 2, seg + 1) % m) % m;
  ans = (ans + seg * solve(on - 3, seg + 1) % m) % m;

  return ans;
}

/* Here is the stardard approach
  You have 0 on computers, and you want to turn them on
  By turning a computer on:
    - Might create a new segment:
      - Turning a computer on the left of all segments, or on the right
        of all segments, or in between a pair of segments
    - Might automatically merge into a existing segment:
      - Turning a computer in the border of a segment
      - Turning a computer in beside the border of a segment
        (the computer in between will turn on automatically)
    - Might merge two seperate segments:
      - Turning a computer in between two segments:
        - When both segments have distance 2:
          - Turning a single one of the ones in between will turn
            the other one automatically and merge the segments
        - When both segments have distance 3:
          - Turning on the computer in the middle will turn the
            other 2 automatically and merge the segments
*/
lli solve2(int on = 0, int seg = 0)
{
  if (on > n || seg < 0) return 0;
  if (on == n) return seg == 1;

  lli &ans = memo[on][seg];
  if (ans != -1) return ans;
  ans = 0;

  // Turning on a segment (it can go into (seg + 1) positions)
  ans = (ans + (seg + 1) * solve2(on + 1, seg + 1) % m) % m;

  // Turn on the computer on the border of a segment
  ans = (ans + 2LL * seg * solve2(on + 1, seg) % m) % m;
  // Turn on two computers on the border of a segment (by turning off the one before the last)
  ans = (ans + 2LL * seg * solve2(on + 2, seg) % m) % m;

  // Two segments merge will only happen through a automatic turn on!
  // So you will have to turn off 2 or 3 computers

  // Mergeing two segments
  ans = (ans + 2LL * (seg - 1) * solve2(on + 2, seg - 1) % m) % m;
  ans = (ans + (seg - 1) * solve2(on + 3, seg - 1) % m) % m;

  return ans;
}

int main()
{
  while (~scanf("%d %lld", &n, &m))
  {
    memset(memo, -1, sizeof(memo));
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}
