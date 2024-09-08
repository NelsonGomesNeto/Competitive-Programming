#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n, k;
char children[maxN + 1];
vector<vector<int>> moves;

int main()
{
  while (scanf("%d %d", &n, &k) != EOF)
  {
    moves.clear();
    scanf(" %s", children);

    int sum = 0;
    while (true)
    {
      vector<int> curr;
      for (int j = 0; j < n - 1; j++)
        if (children[j] == 'R' && children[j + 1] == 'L')
        {
          children[j] = 'L', children[j + 1] = 'R';
          curr.push_back(j++), sum++;
        }
      if (curr.empty()) break;
      moves.push_back(curr);
    }

    if (sum < k || moves.size() > k) printf("-1\n");
    else
    {
      vector<vector<int>> ans;
      bool done = false;
      int s = 0;
      for (int i = 0; i < moves.size() && !done; i++)
        for (int j = 0; j < moves[i].size() && !done; j++)
        {
          if (s + 1 + (moves.size() - i - 1) == k)
          {
            done = true;
            vector<int> aux;
            for (int k = j; k < moves[i].size(); k++)
              aux.push_back(moves[i][k]);
            ans.push_back(aux);
            for (int k = i + 1; k < moves.size(); k++)
              ans.push_back(moves[k]);
            break;
          }
          ans.push_back({{moves[i][j]}}), s++;
        }

      for (vector<int> &a: ans)
      {
        printf("%d", (int)a.size());
        for (int aa: a) printf(" %d", aa + 1);
        printf("\n");
      }
    }
  }
  return 0;
}
