#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

string s;

int main()
{
  cin >> s;

  int leftGames = 0, rightGames = 0;
  int leftPoints = 0, rightPoints = 0;
  int server = 0; // 0 - left, 1 - right
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == 'S') // server
    {
      if (server)
        rightPoints++, server = 1;
      else
        leftPoints++, server = 0;
    }
    else if (s[i] == 'R')
    {
      if (!server)
        rightPoints++, server = 1;
      else
        leftPoints++, server = 0;
    }
    else // print
    {
      if (leftGames == 2 || rightGames == 2)
      {
        if (leftGames == 2) printf("%d (winner) - %d\n", leftGames, rightGames);
        else printf("%d - %d (winner)\n", leftGames, rightGames);
      }
      else
      {
        if (server) printf("%d (%d) - %d (%d*)\n", leftGames, leftPoints, rightGames, rightPoints);
        else printf("%d (%d*) - %d (%d)\n", leftGames, leftPoints, rightGames, rightPoints);
      }
    }

    if (leftPoints == 10 || (leftPoints >= 5 && leftPoints - rightPoints >= 2))
      leftGames++, leftPoints = 0, rightPoints = 0;
    if (rightPoints == 10 || (rightPoints >= 5 && rightPoints - leftPoints >= 2))
      rightGames++, leftPoints = 0, rightPoints = 0;
  }

  return 0;
}