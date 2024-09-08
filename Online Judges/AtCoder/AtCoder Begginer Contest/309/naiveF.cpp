#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5;
int n;
vector<int> originalBox[maxN], box[maxN];

bool bigger(int i, int j, const vector<int>& p0)
{
  return box[i][p0[0]] > box[j][0]
      && box[i][p0[1]] > box[j][1]
      && box[i][p0[2]] > box[j][2];
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; ++i)
    {
      originalBox[i].clear();
      originalBox[i].resize(3);
      for (auto &a : originalBox[i])
        scanf("%d", &a);
      box[i] = originalBox[i];
    }

    bool ans = false;
    vector<int> p0 = {0, 1, 2};
    do
    {
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          ans |= bigger(i, j, p0);
    } while (next_permutation(p0.begin(), p0.end()) && !ans);


    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
