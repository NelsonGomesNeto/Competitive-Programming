#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;

/*
  You always need to cut in such a way the every polygon is quadrilateral

  There's a rotation of poins in which he initial cut will be from 1 to 2*n - 2
  and from there, you can have the following cuts: (let's call lo = 1, hi = 2*n - 2)
    lo + 1, hi - 1  }
    lo + 2, hi      } are possible cut points from lo, hi
    lo, hi - 2      }
    lo + 3, hi - 3  } <-- this one will create two lines (lo, lo + 3) and (hi, hi - 3)
  This way, the amount of cuts isn't part of the state (since it can be implied from lo and hi)
  So memo: [maxN, lo][maxN, hi]

  And the overall complexity is O(n^2 * (n)) (because of the rotations)
*/

const double inf = 1e15;
struct Point
{
  double x, y;
  double distance(Point &other)
  {
    return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
  }
};
const int maxN = 2e2; int n;
Point points[maxN], aux[maxN];

double dist(int lo, int hi)
{
  return points[lo].distance(points[hi]);
}

/*
  Bom, parece que a ideia aqui vai ser
  Traçar uma reta entre dois pontos
  Isso vai dividir em pontos da esquerda e pontos da direita
  Aí a quantidade de cortes que cada lado precisa fazer ser:
    (pointsCount >> 1) - 2

  The problem with this strategy is that you're not considering the entire range
  Example:
    You start with lo = 0, hi = 2*n - 1
    Split into [lo(0), i] and [i, hi(2*n-1)]
    But notice that actually: [i, hi] should have 0 in it
    Because of that, you run into some problems
*/

double memo[maxN][maxN][maxN][3];
double solve(int lo = 0, int hi = 2*n - 1, int remPoints = 0)
{
  int requiredCuts = ((hi - lo + 1) >> 1) - 2;
  if (requiredCuts == 0) return hi - lo + 1 >= 4 ? remPoints ? dist(hi, hi - 3) : dist(lo, lo + 3) : inf;
  printf("[%2d, %2d; %2d] - %2d\n", lo, hi, remPoints, requiredCuts);

  double ans = hi - lo + 1 == 4 ? dist(lo, hi) : inf;
  for (int i = lo + 3; abs(hi - i) + 1 >= 4; i += 2)
    ans = min(ans, solve(lo, i, 0) + solve(i, hi, 1) + (i != lo + 3 ? max(dist(hi, i), dist(lo, i)) : 0));
  // for (int i = hi - 3; i >= lo + 3; i -= 2)
  //   ans = min(ans, solve(lo, i, 1) + dist(i, hi) + solve(i, hi, 0));

  return ans;
}

double brute2(vector<Point> ps, int cuts = 0)
{
  if (cuts == n - 2) return 0;

  double ans = 1e18;
  for (int i = 0; i + 3 < ps.size(); i++)
  {
    vector<Point> nwps;
    for (int j = 0; j < ps.size(); j++)
      if (j != i + 1 && j != i + 2)
        nwps.push_back(ps[j]);
    ans = min(ans, ps[i].distance(ps[i + 3]) + brute2(nwps, cuts + 1));
  }
  return ans;
}
double brute()
{
  vector<Point> ps;
  for (int i = 0; i < 2*n; i++)
    ps.push_back(points[i]);
  return brute2(ps);
}

int main()
{
  scanf("%d", &n);
  DEBUG printf("{");
  for (int i = 0; i < 2*n; i ++)
  {
    scanf("%lf %lf", &points[i].x, &points[i].y);
    DEBUG if (i) printf(", ");
    DEBUG printf("{%lf, %lf}", points[i].x, points[i].y);
  }
  DEBUG printf("}\n");

  double ans = inf;
  for (int i = 0; i <= 2*n; i++)
  {
    for (int j = 0; j < 2*n; j++)
      for (int k = 0; k < 2*n; k++)
        for (int p = 0; p < n; p++)
          memo[j][k][p][0] = memo[j][k][p][1] = memo[j][k][p][2] = -1;
    double res = solve();
    // double res2 = brute();
    DEBUG printf("%d - %.4lf\n", i, res);
    ans = min(ans, res);

    rotate(points, points+1, points+2*n);
  }

  printf("%.4lf\n", ans);

  return(0);
}