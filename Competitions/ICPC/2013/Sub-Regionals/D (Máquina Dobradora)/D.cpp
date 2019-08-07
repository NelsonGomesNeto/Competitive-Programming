#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 15; int n, m;
struct Tape
{
  int data[maxN], size;
  void init(int sz)
  {
    size = sz;
    for (int i = 0; i < size; i ++)
      data[i] = 0;
  }
  bool operator<(const Tape &t) const
  {
    if (size < t.size) return(true);
    if (size == t.size)
      for (int i = 0; i < size; i ++)
      {
        if (data[i] < t.data[i])
          return(true);
        if (data[i] > t.data[i])
          return(false);
      }
    return(true);
  }
  bool operator==(const Tape &t) const
  {
    if (size != t.size) return(false);
    for (int i = 0; i < size; i ++)
      if (data[i] != t.data[i])
        return(false);
    return(true);
  }
  Tape fold(int at)
  {
    // printf("\t\tat: %d || %d -- %d\n", at, size, max(at, size - at));
    Tape temp; temp.init(max(at, size - at));
    for (int i = at - 1; i >= 0; i --)
      temp.data[temp.size - at + i] = data[i];
    for (int i = at, a = 1; i < size; i ++, a ++)
      temp.data[temp.size - a] += data[i];
    return(temp);
  }
  void print()
  {
    printf("%2d - ", size);
    for (int i = 0; i < size; i ++) printf("%3d%c", data[i], i < size - 1 ? ' ' : '\n');
  }
};
Tape origin, destination;

bool solve(Tape u = origin, bool done = false)
{
  if (u == destination) return(true);

  for (int i = done, end = u.size - destination.size; i <= end; i ++)
  {
    if (solve(u.fold(i), true)) return(true);
    if (solve(u.fold(u.size - i), true)) return(true);
  }

  return(false);
}

int main()
{
  while (scanf("%d", &n) != EOF && n)
  {
    origin.size = n;
    int originSum = 0, destinationSum = 0;
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &origin.data[i]);
      originSum += origin.data[i];
    }
    scanf("%d", &m);
    destination.size = m;
    for (int i = 0; i < m; i ++)
    {
      scanf("%d", &destination.data[i]);
      destinationSum += destination.data[i];
    }

    bool can = originSum >= destinationSum ? solve() : false;
    printf("%c\n", can ? 'S' : 'N');
  }
  return(0);
}