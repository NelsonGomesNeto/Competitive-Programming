#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = LONG_LONG_MAX;

// Used on Educational DP Contest - Z (Frog 3)

// y = m*x + b
struct Line
{
  lli m, b;
  lli value(lli x)
  {
    return m*x + b;
  }
};
struct LiChaoTree
{
  int size;
  vector<Line> lines;
  LiChaoTree() { }
  LiChaoTree(int sz) : size(sz)
  {
    Line nilLine = {0, inf};
    lines.resize(4*sz, nilLine);
  }
  void addLine(Line newLine) { addLine(newLine, 1, 0, size - 1); }
  void addLine(Line &newLine, int i, int lo, int hi)
  {
    int mid = (lo + hi) >> 1;
    bool leftEval = newLine.value(lo) < lines[i].value(lo);
    bool midEval = newLine.value(mid) < lines[i].value(mid);
    if (midEval) swap(newLine, lines[i]);

    if (lo == hi - 1) return;
    if (leftEval != midEval) addLine(newLine, 2*i, lo, mid);
    else addLine(newLine, 2*i + 1, mid, hi);
  }
  lli get(int x) { return get(x, 1, 0, size - 1); }
  lli get(int x, int i, int lo, int hi)
  {
    if (lo == hi - 1) return lines[i].value(x);
    int mid = (lo + hi) >> 1;
    if (x < mid) return min(lines[i].value(x), get(x, 2*i, lo, mid));
    else return min(lines[i].value(x), get(x, 2*i + 1, mid, hi));
  }
};
LiChaoTree liChaoTree;

int main()
{
  
  return 0;
}