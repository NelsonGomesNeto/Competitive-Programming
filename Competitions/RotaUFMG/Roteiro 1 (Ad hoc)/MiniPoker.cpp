#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, t = 0; scanf("%d", &n);
  while (n -- > 0)
  {
    if (t) printf("\n");
    printf("Teste %d\n", ++ t);

    int c[5], points = 0, done = 0;
    for (int i = 0; i < 5; i ++) scanf("%d", &c[i]);

    sort(c, c+5);
    int is = 1; // 1
    for (int i = 0; i < 5 - 1; i ++)
      if (c[i] != c[i + 1] - 1)
        is = 0;
    if (is && !done) { points += 200 + c[0]; done = 1; }

    if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3] && c[3] != c[4] && !done) { points += 180 + c[0]; done = 1; }
    if (c[0] != c[1] && c[1] == c[2] && c[2] == c[3] && c[3] == c[4] && !done) { points += 180 + c[1]; done = 1; }

    if ((c[0] == c[1] && c[1] == c[2] && c[3] == c[4]) || (c[0] == c[1] && c[2] == c[3] && c[3] == c[4]) && !done) { points += 160 + ((c[0] == c[1] && c[1] == c[2]) ? c[0] : c[4]); done = 1; }

    if (c[0] == c[1] && c[1] == c[2] && c[0] != c[3] && c[0] != c[4] && c[3] != c[4] && !done) { points += 140 + c[0]; done = 1; } // 4
    if (c[0] != c[1] && c[0] != c[4] && c[4] != c[1] && c[1] == c[2] && c[2] == c[3] && !done) { points += 140 + c[1]; done = 1; }
    if (c[0] != c[1] && c[1] != c[2] && c[0] != c[2] && c[2] == c[3] && c[3] == c[4] && !done) { points += 140 + c[2]; done = 1; }

    int pair1 = -1 , pair2 = -1, odd = -1; // 5
    for (int i = 0; i < 5 - 1; i ++)
      if (c[i] == c[i + 1] && pair1 == -1)
        pair1 = c[i ++];
      else if (c[i] == c[i + 1] && c[i] != pair1)
        pair2 = c[i];
      else
        odd = (c[i] == pair1 || c[i] == pair2) ? c[i + 1] : c[i];
    //printf("%d %d %d\n", odd, pair1, pair2);
    if (pair1 != -1 && pair2 != -1 && odd != -1 && odd != pair1 && odd != pair2 && !done) { points += 2 * pair1 + 3 * pair2 + 20; done = 1; }

    int pair = -1; is = 0; // 6
    for (int i = 0, e = 1; i < 5 - 1; i ++)
    {
      if (c[i] == c[i + 1])
        pair = c[i];
      else if (c[i] != c[i + 1])
        e ++;
      if (e == 4 && pair != -1) is = 1;
    }
    if (is && !done) points += pair;

    printf("%d\n", points);
  }
  return(0);
}