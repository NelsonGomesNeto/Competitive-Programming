#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 200; int n, m, k;
struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
  void add(int ii, int jj)
  {
    int ni = i + ii, nj = j + jj;
    if (ni >= 0 && ni < n)  
      i = ni;
    if (nj >= 0 && nj < m)
      j = nj;
  }
  bool operator!=(const Pos &other) { return i != other.i || j != other.j; }
  bool operator==(const Pos &other) { return i == other.i && j == other.j; }
};
bool done[maxN]; int totalDone = 0;
Pos positions[maxN], destinations[maxN];

int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};
void moveAll(int d)
{
  for (int i = 0; i < k; i++)
  {
    positions[i].add(di[d], dj[d]);
    if (positions[i] == destinations[i])
    {
      totalDone += !done[i];
      done[i] = true;
    }
  }
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    memset(done, false, sizeof(done)), totalDone = 0;
    int lowest = 0, righest = 0;
    for (int i = 0; i < k; i++)
    {
      positions[i].read();
      lowest = max(lowest, positions[i].i);
      righest = max(righest, positions[i].j);
    }
    for (int i = 0; i < k; i++)
    {
      destinations[i].read();
      if (positions[i] == destinations[i])
        done[i] = true, totalDone++;
    }

    string ans = "";
    for (int i = 0; i < lowest && totalDone < k; i++) ans += 'U', moveAll(1);
    for (int i = 0; i < righest && totalDone < k; i++) ans += 'L', moveAll(3);
    for (int i = 0; i < n && totalDone < k; i++)
    {
      for (int j = 0; j < m - 1 && totalDone < k; j++)
      {
        if (i & 1)
          ans += 'L', moveAll(3);
        else
          ans += 'R', moveAll(2);
      }
      if (i < n - 1 && totalDone < k)
        ans += 'D', moveAll(0);
    }
    // for (int i = 0; i < k; i++)
    // {
    //   while (!done[i] && ans.size() <= 2*n*m)
    //   {
    //     if (positions[i].i < destinations[i].i)
    //       moveAll(0), ans += 'D';
    //     else if (positions[i].i > destinations[i].i)
    //       moveAll(1), ans += 'U';
    //     else if (positions[i].j < destinations[i].j)
    //       moveAll(2), ans += 'R';
    //     else
    //       moveAll(3), ans += 'L';
    //     DEBUG printf("%d - %d %d %d %d\n", i, positions[i].i + 1, positions[i].j + 1, destinations[i].i + 1, destinations[i].j + 1);
    //   }
    // }

    // printf("%d %d\n%s\n", (int)ans.size(), 2*n*m, ans.c_str());
    if (ans.size() <= 2*n*m)
      printf("%d\n%s\n", (int)ans.size(), ans.c_str());
    else
      printf("-1\n");
  }
  return 0;
}