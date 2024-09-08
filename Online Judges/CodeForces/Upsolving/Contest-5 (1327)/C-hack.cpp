/// **********************************************************************************************************************
/// ********************************** ~ CODE - TrI HiEn Diamond ❤ LINH CHI ~ ******************************************
/// **********************************************************************************************************************
#include <bits/stdc++.h>
#define fi first
#define se second
#define mem0(CHI)  memset(CHI,0,sizeof(CHI))
#define memt(CHI)  memset(CHI,true,sizeof(CHI))
#define mem1(CHI)  memset(CHI,1,sizeof(CHI))
#define mp make_pair
#define PB push_back
#define btcount(x) __builtin_popcount(x)
#define sqr(x) ((x) * (x))
#define INF 9999999999
#define MOD 1000000007
#define maxn 100005

#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i,n) for (int i=0;i<(n);i=i+1)

#define BAYMAXX ""

#define ull unsigned long long
#define uld unsigned long double
#define ld long double
#define ll long long

const long base = 151 ;
const ll MM = 1ll * MOD * MOD ;

using namespace std ;

typedef pair <long, long> pii;
typedef pair <ll, ll> pll;
typedef vector <int> vi;
typedef vector <string> vs;

// bit operater
int BIT(int i,ll x) { return(x&(1<<i));}
ll ONBIT(int i,ll x){ return(x|(1<<i));}
ll OFFBIT(int i,ll x){return (x& ~(1<<i));}
ll FLIPBIT(int i,ll x){return (x^(1<<i));}
ll NUMBIT(ll x) {return __builtin_popcount(x);}

// math
template<class T> T GCD(T a, T b){ T r; while (b != 0) { r = a % b; a = b; b = r; } return a;}
template<class T> T LCM(T a, T b) { return a / GCD(a, b) * b; }
long long m,n;
void read()
{
    cin >> n >> m ;
    ll res =(m+1)*(n-1) ;
    ll res2 = 2 *(m-1) ;
    cout << res+res2 << endl;
    for(long i=1;i<n;i++) cout <<"U";
    for(long i=1;i<m;i++) cout <<"L";
    for(long i=1;i<m;i++) cout <<"R";
    for( long i=2;i<=n;i++)
    {
        cout <<"D";
        if( i % 2 )
        {
            for(long i=1;i<m;i++) cout <<"R";
        }
        else
            for(long i=1;i<m;i++) cout <<"L";
    }

}
int main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(NULL) ; cout.tie(NULL) ;
    //freopen( BAYMAXX".inp" , "r" , stdin ) ;
    //freopen( BAYMAXX".out" , "w" , stdout ) ;
    read() ;
}
