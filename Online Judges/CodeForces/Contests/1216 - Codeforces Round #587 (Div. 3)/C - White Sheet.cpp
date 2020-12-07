#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxX = 1e6 + 1;
struct Point
{
  int x, y;
  bool read() { return scanf("%d %d", &x, &y) != EOF; }
};
struct Sheet
{
  Point p1, p2;
  bool read() { return p1.read() && p2.read(); }
};
Sheet sheets[3];

int main()
{
  while (sheets[0].read())
  {
    sheets[1].read(), sheets[2].read();
    set<int> xs, ys;
    for (int i = 0; i < 3; i ++)
    {
      xs.insert(sheets[i].p1.x), xs.insert(sheets[i].p2.x);
      ys.insert(sheets[i].p1.y), ys.insert(sheets[i].p2.y);
    }
    int compressedX[maxX], compressedY[maxX], cx = 0, cy = 0;
    for (int i: xs) compressedX[i] = cx += 2;
    for (int i: ys) compressedY[i] = cy += 2;
    for (int i = 0; i < 3; i ++)
    {
      sheets[i].p1.x = compressedX[sheets[i].p1.x], sheets[i].p2.x = compressedX[sheets[i].p2.x];
      sheets[i].p1.y = compressedY[sheets[i].p1.y], sheets[i].p2.y = compressedY[sheets[i].p2.y];
    }

    int mat[cy + 1][cx + 1]; memset(mat, 0, sizeof(mat));
    for (int i = 1; i < 3; i ++)
      for (int y = min(sheets[i].p1.y, sheets[i].p2.y); y <= max(sheets[i].p1.y, sheets[i].p2.y); y ++)
        for (int x = min(sheets[i].p1.x, sheets[i].p2.x); x <= max(sheets[i].p1.x, sheets[i].p2.x); x ++)
          mat[y][x] = 1;
    bool can = false;
    for (int y = min(sheets[0].p1.y, sheets[0].p2.y); y <= max(sheets[0].p1.y, sheets[0].p2.y); y ++)
      for (int x = min(sheets[0].p1.x, sheets[0].p2.x); x <= max(sheets[0].p1.x, sheets[0].p2.x); x ++)
      {
        if (!mat[y][x])
          can = true;
        // printf("%d%c", mat[y][x], x < max(sheets[0].p1.x, sheets[0].p2.x) ? ' ' : '\n');
      }
    printf("%s\n", can ? "YES" : "NO");
  }
  return(0);
}
