#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b, c, d;

int main()
{
  while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF)
  {
    bool can = true;
    vector<int> zeroOne;
    for (int i = 0, turn = a >= b ? 0 : 1; a > 0; i ++, turn = turn == 0 ? 1 : 0)
    {
      if (turn == 0) zeroOne.push_back(0), a --;
      else zeroOne.push_back(1), b --;
    }
    if (a < 0 || b < 0) can = false;

    vector<int> twoThree;
    for (int i = 0, turn = d >= c ? 3 : 2; d > 0; i ++, turn = turn == 2 ? 3 : 2)
    {
      if (turn == 3) twoThree.push_back(3), d --;
      else twoThree.push_back(2), c --;
    }
    if (d < 0 || c < 0) can = false;

    vector<int> oneTwo;
    for (int i = 0, turn = b >= c ? 1 : 2; b > 0 || c > 0; i ++, turn = turn == 1 ? 2 : 1)
    {
      if (turn == 1) oneTwo.push_back(1), b --;
      else oneTwo.push_back(2), c --;
    }
    if (a != 0 || b != 0 || c != 0 || d != 0) can = false;

    vector<vector<int>> ans;
    for (int i = 0; i < 2; i ++)
      for (int j = 0; j < 2; j ++)
        for (int k = 0; k < 2; k ++)
        {
          ans.push_back(vector<int>());
          if (i) ans.back().insert(ans.back().end(), zeroOne.rbegin(), zeroOne.rend());
          else ans.back().insert(ans.back().end(), zeroOne.begin(), zeroOne.end());
          if (j) ans.back().insert(ans.back().end(), oneTwo.rbegin(), oneTwo.rend());
          else ans.back().insert(ans.back().end(), oneTwo.begin(), oneTwo.end());
          if (k) ans.back().insert(ans.back().end(), twoThree.rbegin(), twoThree.rend());
          else ans.back().insert(ans.back().end(), twoThree.begin(), twoThree.end());
        }
    int valid = -1;
    for (int j = 0; j < ans.size(); j ++)
    {
      bool isValid = true;
      for (int i = 0; i < ans[j].size() - 1; i ++)
        if (abs(ans[j][i + 1] - ans[j][i]) != 1)
          isValid = false;
      if (isValid)
        valid = j;
    }
    can = can && valid != -1;

    if (can)
    {
      printf("YES\n");
      for (int i = 0; i < ans[valid].size(); i ++)
        printf("%d%c", ans[valid][i], i < ans[valid].size() - 1 ? ' ' : '\n');
    }
    else
      printf("NO\n");
  }
  return 0;
}