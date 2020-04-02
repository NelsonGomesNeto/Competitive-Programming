#define ldouble long double
const double EPS = 1e-7;

struct Point
{
  double x, y;
  Point operator+(const Point &other) { return Point{x + other.x, y + other.y}; }
  Point operator-(const Point &other) { return Point{x - other.x, y - other.y}; }
  Point operator*(const double a) { return Point{x * a, y * a}; }
  double operator*(const Point &other) { return x * other.x + y * other.y; }
  double distance(Point &other) { return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y)); }
  double cross(Point &other) { return x*other.y - y*other.x; }
  Point rotate(double rad) { return Point{x * cos(rad), - y * sin(rad), x * sin(rad) + y * cos(rad)}; }
  Point normalized()
  {
    double norm = sqrt(x*x + y*y);
    return Point{x / norm, y / norm};
  }
  Point pointOfIntercection(Point &p1, Point &p2)
  {
    Point v = p2 - p1, u = p1 - *this, w = p2 - *this;
    double vu = v * u, vv = v * v;
    double t = -vu / vv;
    // return pointBetween(t, p1, p2); if it's a line and not a segment
    if (t >= 0 && t <= 1) return vectorToSegment(t, p1, p2);
    return u*u <= w*w ? p1 : p2;
  }
  bool ccw(Point &B, Point &C)
  {
    return (C.y - this->y) * (B.x - this->x) > (B.y - this->y) * (C.x - this->x);
  }
  Point vectorToSegment(double t, Point &p1, Point &p2)
  {
    return Point({(1 - t) * p1.x + t * p2.x,
                  (1 - t) * p1.y + t * p2.y});
  }
  void print() { printf("%.4lf %.4lf\n", x, y); }
};

struct Circle
{
  Point center; double radious;
  bool contains(Point &p) { return center.distance(p) <= radious + EPS; }
  pair<Point, Point> circleIntersections(Circle &other)
  {
    double d = center.distance(other.center);
    double u = acos((other.radious*other.radious + d*d - radious*radious) / (2.0*other.radious*d));
    Point dc = (center - other.center).normalized() * other.radious;
    return pair<Point, Point>
    {
      other.center + dc.rotate(u),
      other.center + dc.rotate(-u)
    };
  }
};

Circle circumCircle(Point &a, Point &b, Point &c)
{
  Point u = Point{(b - a).y, (a - b).x};
  Point v = Point{(c - a).y, (a - c).x};
  Point n = (c - b) * 0.5;
  double t = u.cross(n) / v.cross(u);
  Point center = ((a + c)*0.5) + v*t;
  return Circle{center, center.distance(a)};
}

Circle minimumCircle(vector<Point> &p)
{
  random_shuffle(p.begin(), p.end());
  Circle circle = Circle{p[0], 0};
  for (int i = 0; i < p.size(); i ++)
  {
    if (circle.contains(p[i])) continue;
    circle = Circle{p[i], 0};
    for (int j = 0; j < i; j ++)
    {
      if (circle.contains(p[j])) continue;
      circle = Circle{(p[j] + p[i])*0.5, p[j].distance(p[i])*0.5};
      for (int k = 0; k < j; k ++)
      {
        if (circle.contains(p[k])) continue;
        circle = circumCircle(p[j], p[i], p[k]);
      }
    }
  }
  return circle;
}

struct Segment
{
  Point p1, p2;
  bool interceptsSegment(Point &q1, Point &q2)
  {
    return this->p1.ccw(q1, q2) != p2.ccw(q1, q2) && this->p1.ccw(p2, q1) != this->p1.ccw(p2, q2);
  }
  bool interceptsSegment(Segment &s)
  {
    return this->interceptsSegment(s.p1, s.p2);
  }
};

/* Closest point to a line:
  a*x + b*y + c = 0:
    x = (b(b*x - a*y) - a*c) / (a^2 + b^2)
    y = (a(-b*x + a*y) - b*c) / (a^2 + b^2)
  two points:
    
*/
/* triangle area given points a, b and c
  1/2 * det({a.x, b.x, c.x},
            {a.y, b.y, c.y},
            {  1,   1,   1})
*/
/* Area of convex polygon:
              |x_1 y_1|
              |x_2 y_2|
  1/2 * "det"(|...    |)
              |x_n y_n|
              |x_1 y_1|
*/
/* point inside a non convex polygon: pnpoly
  bool insidePolygon(int x, int y)
  {
    bool c = false;
    for (int i = 0; i < n; i ++)
    {
      int x1 = points[i].x, x2 = points[i + 1].x, y1 = points[i].y, y2 = points[i + 1].y;

      // iff you can guarantee that there will be only right angled line
      // if (y1 == y2 && y == y1 && x >= min(x1, x2) && x <= max(x1, x2)) return(true);
      // if (x1 == x2 && x == x1 && y >= min(y1, y2) && y <= max(y1, y2)) return(true);

      double h = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)), a = sqrt(pow(x - x1, 2) + pow(y - y1, 2)), b = sqrt(pow(x - x2, 2) + pow(y - y2, 2));
      if (a + b - h <= 1e-6) return(true);
      if ((y1 > y) != (y2 > y) && (x < (x2 - x1) * (double) (y - y1) / (y2 - y1) + x1))
        c = !c;
    }
    return(c);
  }
*/
/* struct Point
  {
    double x, y, d; int id;
    double dist(const Point &a) { return(sqrt((a.x - x)*(a.x - x) + (a.y - y)*(a.y - y))); }
    bool collinear(const Point &a, const Point &b) { return((x - a.x)*(a.y - b.y) - (a.x - b.x)*(y - a.y) == 0); }
  };
*/
/* struct QuadTree
  {
    int inside;
    QuadTree *quadrants[4];
  };
  QuadTree *root;
  QuadTree* newQuadTree(int lox = minX, int loy = minY, int hix = maxX, int hiy = maxY)
  {
    if (lox > hix || loy > hiy) return(NULL);
    QuadTree *temp = (QuadTree*) malloc(sizeof(QuadTree));
    temp->inside = 0;
    for (int i = lowerBound(lox); i < n && points[i].x <= hix; i ++)
      temp->inside += points[i].inside(lox, loy, hix, hiy);
    if ((lox == hix && loy == hiy) || temp->inside == 0)
    {
      for (int i = 0; i < 4; i ++) temp->quadrants[i] = NULL;
      return(temp);
    }
    int midx = (lox + hix) >> 1, midy = (loy + hiy) >> 1;
    temp->quadrants[0] = newQuadTree(lox, loy, midx, midy);
    temp->quadrants[1] = newQuadTree(lox, midy + 1, midx, hiy);
    temp->quadrants[2] = newQuadTree(midx + 1, midy + 1, hix, hiy);
    temp->quadrants[3] = newQuadTree(midx + 1, loy, hix, midy);
    return(temp);
  }

  int query(int qlox, int qloy, int qhix, int qhiy, int lox = minX, int loy = minY, int hix = maxX, int hiy = maxY, QuadTree *curr = root)
  {
    if (lox > hix || loy > hiy || curr == NULL) return(0);
    if (qlox > hix || qhix < lox || qloy > hiy || qhiy < loy) return(0);
    if (lox >= qlox && loy >= qloy && hix <= qhix && hiy <= qhiy) return(curr->inside);
    int ans = 0;
    int midx = (lox + hix) >> 1, midy = (loy + hiy) >> 1;
    ans += query(qlox, qloy, qhix, qhiy, lox, loy, midx, midy, curr->quadrants[0]);
    ans += query(qlox, qloy, qhix, qhiy, lox, midy + 1, midx, hiy, curr->quadrants[1]);
    ans += query(qlox, qloy, qhix, qhiy, midx + 1, midy + 1, hix, hiy, curr->quadrants[2]);
    ans += query(qlox, qloy, qhix, qhiy, midx + 1, loy, hix, midy, curr->quadrants[3]);
    return(ans);
  }
*/