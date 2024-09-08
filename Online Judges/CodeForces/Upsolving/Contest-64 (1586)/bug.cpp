#include <bits/stdc++.h>

using namespace std;

void run_test_case() {
    int n; cin >> n;
    int pos = 1;
    while(1) {
        cout << "? ";
        for(int i = 0; i < n; i++) {
            if(i + 1 == pos) cout << 2;
            else cout << 1;
            cout << ' ';
        }
        cout << endl;
        cout.flush();
        int ans; cin >> ans;
        if(ans == 0) break;
        else pos = ans;
    }
    vector<int> ps;
    ps.push_back(pos);
    for(int i = 0; i < n - 1; i++) {
        cout << "? ";
        int ls = ps.back();
        for(int j = 0; j < n; j++) {
            if(j + 1 == ls) cout << 1;
            else cout << 2;
            cout << " ";
        }
        cout << endl;
        cout.flush();
        int ans; cin >> ans;
        ps.push_back(ans);
    }
    vector<int> ans(n);
    for(int i = 0; i < n; i++) {
        ans[ps.back() - 1] = i + 1;
        ps.pop_back();
    }
    cout << "! ";
    for(int i : ans) cout << i << ' ';
    cout << endl;
    cout.flush();
}

int32_t main() {

    //int test_cases; cin >> test_cases; while(test_cases--) 
        run_test_case();
}

//CHEK:
//  OUT OF BONDS
//  PRECISION
//  DIVISIONS BY ZERO
//  COMPLEXITY
//	OVERFLOWS