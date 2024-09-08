#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct Point {
  lli x, y;
  bool Read() {
    return ~scanf("%lld %lld", &x, &y);
  }
  void Print(string pre) {
    printf("%s(%lld, %lld)\n", pre.c_str(), x, y);
  }
};
Point taka, cargo, target;

bool Between(lli a, lli l, lli r) {
  return (l <= a && a <= r) || (r <= a && a <= l);
}

lli MoveTo(const Point& t) {
  lli dx = t.x - taka.x;
  lli dy = t.y - taka.y;
  lli res = abs(dx) + abs(dy);

  if (dx == 0 && dy != 0 && cargo.x == t.x && Between(cargo.y, taka.y, t.y)) {
    res += 2;
  } else if (dx != 0 && dy == 0 && cargo.y == t.y && Between(cargo.x, taka.x, t.x)) {
    res += 2;
  }

  return res;
}

int main() {
  while (taka.Read()) {
    cargo.Read();
    target.Read();

    lli dx = target.x - cargo.x;
    lli dy = target.y - cargo.y;
    Point start_x = Point{dx < 0 ? cargo.x + 1 : cargo.x - 1, cargo.y};
    Point start_y = Point{cargo.x, dy < 0 ? cargo.y + 1 : cargo.y - 1};

    lli ans = abs(dx) + abs(dy);
    if (dx != 0 && dy != 0)
      ans += 2;

    if (dx == 0 && dy == 0) {
      // nothing
    } else if (dx == 0 && dy != 0) {
      ans += MoveTo(start_y);
    } else if (dx != 0 && dy == 0) {
      ans += MoveTo(start_x);
    } else {  // dx == 0 && dy == 0
      ans += min(MoveTo(start_x), MoveTo(start_y));
    }

    DEBUG {
      start_x.Print("\t");
      printf("\t%lld | %lld\n", dx, MoveTo(start_x));
      start_y.Print("\t");
      printf("\t%lld | %lld\n", dy, MoveTo(start_y));
    }

    printf("%lld\n", ans);
  }
  return 0;
}
