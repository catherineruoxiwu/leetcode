#include <bits/stdc++.h>

using namespace std;

#define read(type) readInt<type>() // Fast read
#define ll long long
#define nL "\n"
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define a first
#define b second
#define vi vector<int>
#define all(x) (x).begin(), (x).end()
#define umap unordered_map
#define uset unordered_set
#define MOD 1000000007
#define imax INT_MAX
#define imin INT_MIN
#define exp 1e9
#define sz(x) (int((x).size()))

ll m(int a) {
    return (a % MOD + MOD) % MOD; 
}


int32_t main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int ttt; cin >> ttt;
    int k = 0;
    while(ttt--) {
        ll R, C;
        cin >> R >> C;
        ll n = min(R-1, C-1);
        ll ans = 0;
        ll t1 = (R * C) % MOD;
        ll t2 = (n * (n + 1)) % MOD;
        ans = (ans + ((t1 * t2) % MOD) * ((1 / 2) % MOD)) % MOD;
        ll t3 = (t2 * t2) % MOD;
        ans = (ans + t3 * ((1 / 4) % MOD)) % MOD;
        t2 = t2 * (2 * n + 1) % MOD;
        ll t4 = ((((C + R) % MOD) * t2) % MOD) % MOD;
        ans = (ans - t4 * ((1 / 6) % MOD)) % MOD;
        cout << endl;
        cout << t1 << " " << t2 << " " << t3 << " " << t4 << " " << endl;
        cout << "Case #" << ++k << ": " << m(ans) << endl;
    }
    return 0;
}