#include <bits/stdc++.h>
using namespace std;

int main()
{
  int tests; scanf("%d", &tests);
  while (tests > 0)
  {
    int trab, posi; scanf("%d %d", &trab, &posi);
    vector<int> list; int i, num;
    for (i = 0; i < trab; i ++)
    {
      cin >> num;
      list.push_back(num);
    }
    int maior = 0;
    int j = 0, tempo = 1;
    while (j < trab)
    {
      for (i = 0; i < trab - 1; i ++)
      {
        if (list[i] < list[i + 1])
        {
          rotate(list.begin(), list.begin() + 1, list.end());
          i --;
          posi --;
          if (posi < 0)
          {
            posi = trab - 1;
          }
        }
      }
      printf("%d\n", list[0]);
      if (posi == 0)
      {
        printf("%d\n", tempo);
        break;
      }
      list.erase(list.begin());
      posi --;
      tempo ++;
      j ++;
    }
    tests --;
  }
}
