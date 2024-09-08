#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

string s;

struct Seed {
  lli source, length;
  lli source_lo, source_hi;

  friend istream& operator>>(istream& stream, Seed& se) {
    stream >> se.source >> se.length;
    se.source_lo = se.source, se.source_hi = se.source + se.length - 1;
    return stream;
  }

  friend ostream& operator<<(ostream& stream, const Seed& se) {
    stream << "[" << se.source_lo << " : " << se.source_hi << "] | " << se.length;
    return stream;
  }
};
vector<Seed> seeds;
void ReadSeeds() {
  getline(cin, s);
  istringstream sinput(s);
  sinput.ignore(6);

  Seed seed;
  while (sinput >> seed) {
    seeds.push_back(seed);
  }
}

const int kMaxMaps = 7;
struct Mapping {
  lli destination, source, length;
  lli source_lo, source_hi;
  lli destination_lo, destination_hi;

  bool Read() {
    if (!getline(cin, s)) return false;
    if (s.size() <= 1) return false;

    istringstream sinput(s);
    sinput >> destination >> source >> length;
    source_lo = source, source_hi = source + length - 1;
    destination_lo = destination, destination_hi = destination + length - 1;
    return true;
  }

  bool Inside(const lli x) {
    return x >= source_lo && x <= source_hi;
  }

  bool operator<(const Mapping& other) const {
    return source_hi < other.source_hi;
  }

  friend ostream& operator<<(ostream& stream, const Mapping& m) {
    stream << "[" << m.source_lo << " : " << m.source_hi << "] -> "
           << "[" << m.destination_lo << " : " << m.destination_hi << "]";
    return stream;
  }
};

vector<vector<Mapping>> maps(kMaxMaps);
void ReadMaps() {
  getline(cin, s);

  for (auto& amap : maps) {
    getline(cin, s);

    Mapping mapping;
    while (mapping.Read()) {
      amap.push_back(mapping);
    }
    sort(amap.begin(), amap.end());
  }
}

lli FindSeedLocation(const lli seed) {
  DEBUG cout << "Processing seed: " << seed << endl;
  lli curr = seed;
  for (auto& amap : maps) {
    DEBUG cout << "\tCurr: " << curr << endl;

    auto cm = lower_bound(amap.begin(), amap.end(), Mapping{.source_hi = curr});
    if (cm == amap.end()) continue;

    DEBUG cout << "\tClosest mapping: " << *cm << " | " << cm->Inside(curr) << endl;

    if (cm->Inside(curr)) {
      const lli dist = curr - cm->source;
      curr = cm->destination + dist;
    }
  }
  DEBUG cout << "\tResult: " << curr << endl;

  return curr;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ReadSeeds();

  ReadMaps();

  lli ans = numeric_limits<lli>::max();
  lli done = 0;
  for (const Seed seed : seeds) {
    for (lli i = seed.source_lo; i <= seed.source_hi; ++i) {
      ans = min(ans, FindSeedLocation(i));
      if (++done % (lli)5e7 == 0) {
        cout << "Done" << endl;
        return 0;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
