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