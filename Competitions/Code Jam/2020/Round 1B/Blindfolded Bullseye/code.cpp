#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const lli maxX = 1e9;
char response[10];

struct Point
{
  lli x, y;
  void print() { printf("%lld %lld\n", x, y); fflush(stdout); }
};

bool done;
int query(Point p)
{
  if (done) return 0;
  p.print();
  scanf(" %s", response);
  if (!strcmp(response, "CENTER"))
  {
    done = true;
    return 2;
  }
  if (!strcmp(response, "HIT")) return 1;
  return 0;
}

lli binarySearch(Point inside, bool upperBound, bool swapAxis = false)
{
  lli lo = -maxX, hi = swapAxis ? inside.x : inside.y;
  if (upperBound) hi = maxX, lo = swapAxis ? inside.x : inside.y;
  DEBUG { printf("! binSearch %lld %lld | %d %d\n", lo, hi, upperBound, swapAxis); fflush(stdout); }

  while (lo < hi)
  {
    lli mid = (lo + hi + upperBound) >> 1LL;
    Point p = Point{swapAxis ? inside.y : inside.x, mid};
    if (swapAxis) swap(p.x, p.y);

    if (upperBound)
    {
      if (query(p)) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (query(p)) hi = mid;
      else lo = mid + 1;
    }
  }
  return lo;
}

int main()
{
  int t;
  lli a, b; scanf("%d %lld %lld", &t, &a, &b);
  while (t--)
  {
    done = false;
    Point inside;

    for (lli dx = 0; dx <= 5; dx ++)
      for (lli dy = 0; dy <= 5; dy ++)
      {
        Point curr = Point{-maxX + (dx*2LL*maxX)/5LL, -maxX + (dy*2LL*maxX)/5LL};
        if (query(curr)) inside = curr;
      }

    DEBUG { printf("! inside: %lld %lld\n", inside.x, inside.y); fflush(stdout); }

    if (done) continue;

    lli ylo = binarySearch(inside, false), yhi = binarySearch(inside, true);

    DEBUG { printf("! ylo: %lld, yhi: %lld\n", ylo, yhi); fflush(stdout); }

    if (done) continue;

    inside.y = (ylo + yhi) >> 1LL;

    lli xlo = binarySearch(inside, false, true), xhi = binarySearch(inside, true, true);

    if (done) continue;

    inside.x = (xlo + xhi) >> 1LL;
    DEBUG { printf("! was final\n"); fflush(stdout); }
    query(inside);
  }
  return 0;
}