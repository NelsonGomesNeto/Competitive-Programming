#include <bits/stdc++.h>
using namespace std;

int dx[6] = {1, 2, 3, 4, 6, 12};

int main()
{
  int tests; scanf("%d", &tests);
  while (tests -- > 0)
  {
    char cards[13];
    scanf("\n%s", cards);

    vector<pair<int, int> > solution;
    for (int i = 6 - 1; i >= 0; i --)
      for (int j = 0; j < 12; j ++)
        if (cards[j] == 'X')
        {
          int rows = dx[5 - i] - 1, pos = j, valid = 1;
          while (rows -- > 0 && valid)
          {
            pos = (pos + dx[i]) % 12;
            if (cards[pos] == 'O') valid = 0;
          }
          if (valid)
          {
            solution.push_back({dx[5 - i], dx[i]});
            break;
          }
        }

    printf("%d", (int) solution.size());
    for (auto i: solution)
      printf(" %dx%d", i.first, i.second);
    printf("\n");
  }
  
  return(0);
}