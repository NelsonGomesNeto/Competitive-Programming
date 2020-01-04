#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4; int s, t;
int suspected[maxN];

int main()
{
  while (scanf("%d %d", &s, &t) != EOF)
  {
    memset(suspected, 0, sizeof(suspected));
    for (int i = 0; i < t; i ++)
    {
      int l, r; scanf("%d %d", &l, &r);
      for (int j = l; j <= r; j ++)
        suspected[j] ++;
    }
    int biggestScore = 0;
    for (int i = 0; i < s; i ++)
      biggestScore = max(biggestScore, suspected[i]);

    vector<pair<int, int>> sequences;
    int biggestSequence = 0;
    for (int i = 0; i < s; i ++)
      if (suspected[i] == biggestScore)
      {
        int j = i;
        while (j + 1 < s && suspected[j + 1] == biggestScore) j ++;
        sequences.push_back({i, j});
        biggestSequence = max(biggestSequence, j - i + 1);
        i = j;
      }

    for (int i = 0; i < s; i ++)
      printf("%d", suspected[i]);
    printf("\n");
    printf("%d\n", biggestScore);
    for (auto &p: sequences)
      printf("%d %d\n", p.first, p.second);
    printf("maior sequencia: %d\n", biggestSequence);
    printf("comeca em: %d\n", sequences[0].first);
    printf("termina em: %d\n", sequences[0].second);
  }
  return 0;
}