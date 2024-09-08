//#define _USE_MATH_DEFINES
#include<bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
using namespace std;
#define ll long long
#define endl "\n"
#define f first
#define s second
#define ar array
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define sz(X) ((int)(X).size())
#define rsz resize
#define pcnt __builtin_popcount
#define sort_unique(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define get_pos(c, x) (lower_bound(c.begin(),c.end(),x)-c.begin())
#define all(X) (X).begin(), (X).end()
#define rall(X) (X).rbegin(), (X).rend()
#define ms(c, x)  memset(c,x,sizeof c)
#define  No(x) cout<<(x?"NO":"No")<<endl
#define  Yes(x) cout<<(x?"YES":"Yes")<<endl
#define  nl cout<<endl;
#define forn(i, n) for(int i = 0; i < int(n); i++)
#define fore(i, l, r) for(int i = l; i <r; i++)
#define foreach(i, x) for(auto i:x)
#define fored(i, l, r) for(int i = r-1; i >=l; i--)
#define ford(i, n) for (int i = n - 1; i >= 0; --i)
using ld = long double;
using ul = unsigned long long;
using db = double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
using vi = vector<int>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<ld>;
using vs = vector<string>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
template<typename T, size_t size>
using va = vector<ar<T, size>>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

namespace input {
    template<class T> void re(complex<T>& x);
    template<class T1, class T2> void re(pair<T1,T2>& p);
    template<class T> void re(vector<T>& a);
    template<class T, size_t SZ> void re(array<T,SZ>& a);

    template<class T> void re(T& x) { cin >> x; }
    void re(double& x) { string t; re(t); x = stod(t); }
    void re(ld& x) { string t; re(t); x = stold(t); }
    template<class Arg, class... Args> void re(Arg& first, Args&... rest) {
        re(first); re(rest...);
    }

    template<class T> void re(complex<T>& x) { T a,b; re(a,b); x = cd(a,b); }
    template<class T1, class T2> void re(pair<T1,T2>& p) { re(p.f,p.s); }
    template<class T> void re(vector<T>& a) { forn(i,sz(a)) re(a[i]); }
    template<class T, size_t SZ> void re(array<T,SZ>& a) { forn(i,SZ) re(a[i]); }
}

using namespace input;

namespace output {
    template<class T1, class T2> void pr(const pair<T1,T2>& x);
    template<class T, size_t SZ> void pr(const array<T,SZ>& x);
    template<class T> void pr(const vector<T>& x);
    template<class T> void pr(const set<T>& x);
    template<class T1, class T2> void pr(const map<T1,T2>& x);

    template<class T> void pr(const T& x) { cout << x; }
    template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
        pr(first); pr(rest...);
    }

    template<class T1, class T2> void pr(const pair<T1,T2>& x) {
        pr(x.f," ",x.s);
    }
    template<class T> void prContain(const T& x) {
        bool fst = 1; for (const auto& a: x) pr(!fst?" ":"",a), fst = 0; // const needed for vector<bool>
    }
    template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
    template<class T> void pr(const vector<T>& x) { prContain(x); }
    template<class T> void pr(const set<T>& x) { prContain(x); }
    template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

    void ps() { pr("\n"); }
    template<class Arg> void ps(const Arg& first) {
        pr(first); ps(); // no space at end of line
    }
    template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
        pr(first," "); ps(rest...); // print w/ spaces
    }
}
using namespace output;

template<class T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template<class T>
bool ckmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

void debug() { cerr << endl; }

template<typename Head, typename... Tail>
void debug(Head H, Tail... T) {
    cerr << ' ' << H;
    debug(T...);
}

#ifdef LOCAL
#define dbg(...) cerr <<__LINE__<<" [[DEBUG]] "<<"(" << #__VA_ARGS__ << "):", debug(__VA_ARGS__)
#else
#define dbg(...)
#endif




inline ll modPow(ll x, ll y, ll mod) {
    ll res = 1;
    x = x % mod;;
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % mod;
        }
        y = y >> 1;
        x = (x * x) % mod;

    }
    return res;
}

const int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};
char dirs[4] = {'R', 'D', 'L', 'U'};
unordered_map<char, int> rdirs = {{'R', 0},
                                  {'D', 1},
                                  {'L', 2},
                                  {'U', 3}};
const int MXN = 1e6 + 5;
const ll mod = 1e9 + 7;
//const int mod = 998244353;
const ll INF = 2e18 + 6;
// const int INF = 1e9 + 7;

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;
    map<pi,int>mp1;
    int x=0,y=0;
    forn(i,sz(s)){
        if(s[i]=='D')x++;
        else y++;
        int g=__gcd(x,y);
        mp1[{x/g,y/g}]++;
        cout<<mp1[{x/g,y/g}]<<' ';
    }
    ps();

}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(10);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int t = 1, tc = 1;
     cin >> t;
    while (t--) {
//        cout<<"Case #"<<tc<<": " ;
        solve();
        tc++;
    }
#ifdef LOCAL
    cerr << endl << "Time elapsed : " << clock() * 1000.0 / CLOCKS_PER_SEC << " ms" << '\n';
#endif
    return 0;
}
//NOTES
//look if it requires ll
// read the statement carefully
// check array bounds and cases for n=1b