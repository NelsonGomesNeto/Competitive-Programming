#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3, maxH = 1e5, regionSize = 25; int h, w, n;
const int gridSize = maxH / regionSize + (maxH % regionSize != 0);
int rows, columns;

string baseLine;
const lli mod = 1e9 + 7;
struct Pos
{
  int i, j; lli hash;
  void read() { scanf("%d %d", &i, &j); i--, j--; hash = (i << 20) + j; }
  Pos getRegionPos()
  {
    int ii = i / regionSize, jj = j / regionSize;
    int hash = ii << 20 + jj;
    return Pos{ii, jj, hash};
  }
  Pos getInsidePos()
  {
    int ii = i % regionSize, jj = j % regionSize;
    lli hash = (ii << 20) + jj;
    return Pos{ii, jj, hash};
  }
  bool operator==(const Pos &other) const { return hash == other.hash; }
  bool operator<(const Pos &other) const { return hash < other.hash; }
};
Pos walls[maxN];

struct RegionAns
{
  // maps from (left and top) to (right and bottom)
  // left, right: 0 to c - 1
  // top, bottom: c to c + r - 1
  vector<vector<lli>> ways;
  vector<string> mat;
};
struct Region
{
  int loi, loj, hii, hij;
  vector<Pos> insideWalls;
  RegionAns *regionAns;
};
vector<vector<Region>> regions;

template <typename General>
struct hash_function {
  size_t operator()(General const& c) const {
    size_t hashValue = 0;
    for (auto i: c) hashValue += hash<string>()(to_string(i.i) + " " + to_string(i.j));
    return(hashValue);
  }
};
// unordered_map<vector<Pos>, RegionAns, hash_function<vector<Pos>>> insideWallsToRegionAns;
map<vector<Pos>, RegionAns> insideWallsToRegionAns;

lli memoRegion[regionSize][regionSize];
void reset(int r, int c)
{
  memset(memoRegion, -1, sizeof(memoRegion));
}
lli regionDfs(vector<string> &mat, int i, int j, int targetI, int targetJ)
{
  if (i > targetI || j > targetJ || mat[i][j] == '#') return 0;
  if (i == targetI && j == targetJ) return 1;
  lli &ans = memoRegion[i][j];
  if (ans != -1) return ans;
  return ans = (regionDfs(mat, i + 1, j, targetI, targetJ) + regionDfs(mat, i, j + 1, targetI, targetJ)) % mod;
}
RegionAns getRegionAns(Region &region)
{
  int r = region.hii - region.loi + 1, c = region.hij - region.loj + 1;

  baseLine = "";
  for (int j = 0; j < c; j++)
    baseLine += '.';


  RegionAns regionAns = RegionAns{};
  regionAns.mat.resize(r, baseLine);
  for (Pos &iw: region.insideWalls)
    regionAns.mat[iw.i][iw.j] = '#';

  regionAns.ways.resize(c + r, vector<lli>(c + r, 0));
  for (int i = 0; i < c + r; i++)
    for (int j = 0; j < c + r; j++)
    {
      int loi = i < c ? 0 : i - c, loj = i < c ? i : 0;
      int hii = j < c ? 0 : j - c, hij = j < c ? j : 0;
      reset(r, c);
      regionAns.ways[i][j] = regionDfs(regionAns.mat, loi, loj, hii, hij);
    }

  return regionAns;
}

lli memo[gridSize][gridSize];
lli dfs(int i = 0, int j = 0)
{
  if (i >= rows || j >= columns) return 0;
  if (i == rows - 1 && j == - 1) return 1;
}

int main()
{

  int tt = 0;
  while (scanf("%d %d %d", &h, &w, &n) != EOF)
  {
    if (tt++) printf("-------------------\n");

    for (int i = 0; i < n; i++)
      walls[i].read();

    rows = h / regionSize + (h % regionSize != 0);
    columns = w / regionSize + (w % regionSize != 0);
    regions.clear();
    regions.resize(rows, vector<Region>(columns));
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
        regions[i][j] = Region{i*regionSize, j*regionSize, min(h - 1, (i + 1)*regionSize - 1), min(w - 1, (j + 1)*regionSize - 1)};

    for (int i = 0; i < n; i++)
    {
      Pos regionPos = walls[i].getRegionPos();
      Pos insidePos = walls[i].getInsidePos();
      regions[regionPos.i][regionPos.j].insideWalls.push_back(insidePos);
    }

    insideWallsToRegionAns.clear();
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++)
      {
        sort(regions[i][j].insideWalls.begin(), regions[i][j].insideWalls.end());
        if (!insideWallsToRegionAns.count(regions[i][j].insideWalls))
          insideWallsToRegionAns[regions[i][j].insideWalls] = getRegionAns(regions[i][j]);
        regions[i][j].regionAns = &insideWallsToRegionAns[regions[i][j].insideWalls];
      }

    DEBUG
      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
          printf("%d %d - (%d, %d) (%d, %d)\n", i, j, regions[i][j].loi, regions[i][j].loj, regions[i][j].hii, regions[i][j].hij);
          vector<string> &mat = insideWallsToRegionAns[regions[i][j].insideWalls].mat;
          for (int i = 0; i < mat.size(); i++)
            printf("\t%s\n", mat[i].c_str());

          if (!regions[i][j].insideWalls.empty())
          {
            printf("\t");
            for (Pos &iw: regions[i][j].insideWalls)
              printf("(%d, %d)\n", iw.i, iw.j);
          }
        }

    memset(memo, -1, sizeof(memo));
    lli ans = dfs();
    printf("%lld\n", ans);
  }
  return 0;
}