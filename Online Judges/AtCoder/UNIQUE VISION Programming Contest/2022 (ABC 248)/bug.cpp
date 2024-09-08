/*---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---*/

#include "bits/stdc++.h"
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define dbg(x...)
#endif

#define rep(i, a, b)	for(int i = a; i < (b); ++i)
#define rrep(a, b, c)	for(int a = (b); a > c; --a)
#define each(a, b)	for(auto& a : b)

#define sz(x)       (int)(x).size()
#define all(a)      (a).begin(),(a).end()
#define rall(a)     (a).rbegin(), (a).rend()

#define vi vector<int>
#define ar array

template<class T> using V = vector<T>;
template<class T> using pq = priority_queue<T>;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define eb emplace_back
#define rsz resize
#define bk back()

#define pi pair<int, int>
#define pl pair<ll, ll>
#define mp make_pair
#define f first
#define s second

#define pct(x) __builtin_popcount(x)
constexpr int fsb(int x) {return __builtin_ffs(x) - 1;} // first set bit
constexpr int log2(int x) {return x == 0 ? 0 : 31-__builtin_clz(x);} // floor(log2(x))
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

template <class T> bool umin(T& a, const T& b){return b<a?a=b, 1:0;}
template <class T> bool umax(T& a, const T& b){return a<b?a=b, 1:0;}

const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

using ll = long long;
using ld = long double;
using str = string;

const int inf = (int)1e9 + 5;
const ll infl = (ll)1e18 + 5;
const ld PI = acos((ld)-1);
const int MOD = 998244353;
const int N = 1e5 + 10;

/*---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---XXX---*/

int n, a[N];
vi g[N];
ll ans = 0;

map<int, pl> dfs(int s, int p){
	map<int, pl> m;
	m[a[s]] = {1, 1};

	each(x, g[s]) if(x != p){
		map<int, pl> m1 = dfs(x, s), m2 = m;
		each(y, m1){
			each(x, m){
				ans += 1ll*__gcd(x.f, y.f)*((y.s.f*x.s.s + x.s.f*y.s.s)%MOD)%MOD;
			}

			ll gc = __gcd(y.f, a[s]);
			m2[gc].f += y.s.f;
			m2[gc].s += (y.s.f + y.s.s);
			m2[gc].s %= MOD;
		}
		ans %= MOD;
		swap(m, m2);
	}

	return m;
}

void solve(){
	cin >> n;
	rep(i, 0, n) cin >> a[i];

	rep(i, 1, n){
		int u, v; cin >> u >> v;
		g[--u].eb(--v);
		g[v].eb(u);
	}

	dfs(1, -1);
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	solve();
}