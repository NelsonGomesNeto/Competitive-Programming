#include <bits/stdc++.h>
#define DEBUG if(0)
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
*/

double memo[maxN][maxN][maxN][3];
double solve(int lo = 1, int hi = 2*n - 2, int between = 2, int cuts = 1, bool left = false)
{
  if (cuts == n - 2) return between == 2 ? 0 : inf;
  double &ans = memo[lo][hi][between][cuts];
  if (0 && ans != -1) return ans;

  // return ans = min({
  //   between == 2 ? solve(lo + 1, hi - 1, 2, cuts + 1) + dist(lo + 1, hi - 1) : inf,
  //   between == 2 ? solve(lo + 2, hi, 2, cuts + 1) + dist(lo + 2, hi) : inf,
  //   between == 2 ? solve(lo, hi - 2, 2, cuts + 1) + dist(lo, hi - 2) : inf,

  //   between == 2 ? solve(lo + 3, hi, 1, cuts + 1, true) + dist(lo, lo + 3) : inf,
  //   between == 2 ? solve(lo, hi - 3, 1, cuts + 1, false) + dist(hi, hi - 3) : inf,

  //   between == 1 && cuts + 2 <= n - 2 ? solve(lo + 3, hi, 2, cuts + 2) + dist(lo, lo + 3) + dist(lo + 3, hi): inf,
  //   between == 1 && cuts + 2 <= n - 2 ? solve(lo, hi - 3, 2, cuts + 2) + dist(hi, hi - 3) + dist(lo, hi - 3): inf,

  //   between == 1 ? solve(lo + 1, hi, 2, cuts + 1) + dist(lo + 1, hi) : inf,
  //   between == 1 ? solve(lo, hi - 1, 2, cuts + 1) + dist(lo, hi - 1) : inf,

  //   between == 1 && left ? solve(lo, hi - 2, 1, cuts + 1, true) + dist(lo - 3, hi - 2) : inf,
  //   between == 1 && left ? solve(lo + 2, hi, 1, cuts + 1, true) + dist(lo - 3, lo + 2) : inf,

  //   between == 1 && !left ? solve(lo + 2, hi, 1, cuts + 1, false) + dist(lo + 2, hi + 3) : inf,
  //   between == 1 && !left ? solve(lo, hi - 2, 1, cuts + 1, false) + dist(hi - 2, hi + 3) : inf
  //   // cuts + 2 <= n - 2 ? solve(lo + 3, hi - 1, cuts + 2) + dist(lo, lo + 3) + dist(lo + 3, hi - 1) : inf,
  //   // cuts + 2 <= n - 2 ? solve(lo + 1, hi - 3, cuts + 2) + dist(hi, hi - 3) + dist(lo + 1, hi - 3) : inf,
  //   // cuts + 1 == n - 2 ? dist(lo, lo + 3) : inf,
  //   // cuts + 1 == n - 2 ? dist(hi, hi - 3) : inf
  // });

  // return ans = min({
  //   solve(lo + 1, hi - 1, cuts + 1) + dist(lo + 1, hi - 1),
  //   solve(lo + 2, hi, cuts + 1) + dist(lo + 2, hi),
  //   solve(lo, hi - 2, cuts + 1) + dist(lo, hi - 2),
  //   cuts + 2 <= n - 2 ? solve(lo + 3, hi - 1, cuts + 2) + dist(lo, lo + 3) + dist(lo + 3, hi - 1) : inf,
  //   cuts + 2 <= n - 2 ? solve(lo + 1, hi - 3, cuts + 2) + dist(hi, hi - 3) + dist(lo + 1, hi - 3) : inf,
  //   cuts + 3 <= n - 2 ? solve(lo + 3, hi - 3, cuts + 3) + dist(lo, lo + 3) + dist(hi, hi - 3) + dist(lo + 3, hi - 3) : inf,
  //   cuts + 3 <= n - 2 ? solve(lo + 6, hi, cuts + 3) + dist(lo, lo + 3) + dist(lo + 3, lo + 6) + dist(lo + 6, hi) : inf,
  //   cuts + 3 <= n - 2 ? solve(lo, hi - 6, cuts + 3) + dist(hi, hi - 3) + dist(hi - 3, hi - 6) + dist(lo, hi - 6) : inf,
    
  //   cuts + 1 == n - 2 ? solve(lo + 3, hi, cuts + 1) + dist(lo, lo + 3) : inf,
  //   cuts + 1 == n - 2 ? solve(lo, hi - 3, cuts + 1) + dist(hi, hi - 3) : inf,
  //   cuts + 2 == n - 2 ? solve(lo + 3, hi - 3, cuts + 2) + dist(lo, lo + 3) + dist(hi, hi - 3) : inf,
  //   cuts + 2 == n - 2 ? solve(lo + 6, hi, cuts + 2) + dist(lo, lo + 3) + dist(lo + 3, lo + 6) : inf,
  //   cuts + 2 == n - 2 ? solve(lo, hi - 6, cuts + 2) + dist(hi, hi - 3) + dist(hi - 3, hi - 6) : inf,
  // });
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
    double res = dist(1, 2*n - 2) + solve();
    // double res2 = brute();
    // DEBUG printf("%d - %.4lf %.4lf\n", i, res, res2);
    ans = min(ans, res);

    rotate(points, points+1, points+2*n);
  }

  printf("%.4lf\n", ans);

  return(0);
}