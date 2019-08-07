#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The idea is to test every possible set of cinemas, each set will be represented
  by an integer (bitmask) where the i-th bit represents whether the i-th cinema
  belongs to that set. Since maxN = 20, it will fit in a integer.

  memo[bitmask] keeps the highest ending time for that set of cinemas

  (from 0 to (1 << n) - 1)
  for every bitmask, we'll try to add a cinema (j) that isn't in the set
    We will try to add it in the end, so: we binarySearch for the last
    movie in that cinema that starts until memo[bitmask], so:
    memo[bitmask | (1 << j)] = max(memo[bitmask | (1 << j)], memo[bitmask], endingTimeOfTheMovie)
    iff it starts until memo[bitmask], of course
  The answer will be the bitmask with less ones that makes memo[bitmask] >= L
*/

const int maxN = 20, maxC = 1e3, inf = 1e9; int n; lli L;
lli durations[maxN];
vector<lli> movies[maxN];
struct Movie
{
  int movie, j; lli end;
  bool operator<(const Movie &m) const { return(end < m.end); }
};
vector<vector<Movie>> nextMovies[maxN];

int upperBound(vector<lli> &movie, lli target)
{
  int lo = 0, hi = movie.size() - 1;
  while (lo < hi)
  {
    int mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    if (movie[mid] <= target) lo = mid;
    else hi = mid - 1;
  }
  return(lo);
}
int countOnes(int number)
{
  int ones = 0;
  while (number)
  {
    ones += number & 1;
    number >>= 1;
  }
  return(ones);
}

lli memo[1 << maxN];
int solve()
{
  int ans = inf;
  for (int bitmask = 0, end = 1 << n; bitmask < end; bitmask ++)
  {
    for (int k = 0; k < n; k ++)
      if (bitmask & (1 << k)) continue;
      else
      {
        int pos = upperBound(movies[k], memo[bitmask]);
        if (movies[k][pos] <= memo[bitmask])
          memo[bitmask | (1 << k)] = max({memo[bitmask | (1 << k)], memo[bitmask], movies[k][pos] + durations[k]});
      }
    if (memo[bitmask] >= L) ans = min(ans, countOnes(bitmask));
  }
  return(ans);
}

int main()
{
  FILE *fin = fopen("movie.in", "rb");
  FILE *fout = fopen("movie.out", "wb");
  fscanf(fin, "%d %lld", &n, &L);
  for (int i = 0, c; i < n; i ++)
  {
    fscanf(fin, "%lld %d", &durations[i], &c);
    for (lli j = 0, t; j < c; j ++)
    {
      fscanf(fin, "%lld", &t);
      movies[i].push_back(t);
    }
  }
  int ans = solve();
  fprintf(fout, "%d\n", ans == inf ? -1 : ans);

  fclose(fin), fclose(fout);

  return(0);
}