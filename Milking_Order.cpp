/*

USACO 2018 US Open Contest, Bronze
Problem 2. Milking Order

https://usaco.org/index.php?page=viewproblem2&cpid=832

TC : O(N^2)

*/
#include <bits/stdc++.h>

using namespace std;
#define ll long long int

int main() {
    freopen("milkorder.in","r",stdin);
    freopen("milkorder.out","w",stdout);
    ll n, m, k;
    cin >> n >> m >> k;
    vector < ll > relative_order_of_cows(m);
    map < ll, ll > cow_rel_pos;
    map < ll, ll > before_one;
    for (ll i = 0; i < m; i++) {
        cin >> relative_order_of_cows[i];
        cow_rel_pos[relative_order_of_cows[i]] = i;
        if (relative_order_of_cows[i] == 1) {
            for (ll j = i - 1; j >= 0; j--) {
                before_one[relative_order_of_cows[j]] = j;
            }
        }
    }
    vector < ll > final_order_of_cows(n, -1);
    bool got_first_cow = false;
    for (ll i = 0; i < k; i++) {
        ll cow_no, pos;
        cin >> cow_no >> pos;
        pos--;
        final_order_of_cows[pos] = cow_no;
        if (cow_no == 1) {
            got_first_cow = true;
            cout << pos + 1 << endl;
        }
    }
    if (got_first_cow) {
        return 0;
    }
    if (cow_rel_pos.count(1)) {
        ll idx = -1;
        for (ll i = n - 1; i >= 0; i--) {
            if (final_order_of_cows[i] != -1) {
                if (before_one.count(final_order_of_cows[i]) != 0) {
                    idx = i;
                    break;
                }
            }
        }
        ll empty = 0;
        ll cnt_bef_one = 0;
        if (idx != -1) {
            ll first = before_one[final_order_of_cows[idx]];
            ll second = cow_rel_pos[1];
            ll diff = second - first - 1;
            for (ll j = idx + 1; j < n; j++) {
                if (final_order_of_cows[j] == -1) {
                    diff--;
                    if (diff == 0) {
                        idx = j;
                        break;
                    }
                }
            }
        }
        for (ll i = 0; i <= idx; i++) {
            if (final_order_of_cows[i] == -1) {
                empty++;
            }
            else {
                if (before_one.count(final_order_of_cows[i])) {
                    cnt_bef_one++;
                }
            }
        }
        for (ll j = idx + 1; j < n; j++) {
            if (final_order_of_cows[j] == -1) {
                ll val = empty - (before_one.size() - cnt_bef_one);
                if (val >= 0) {
                    cout << j + 1 << endl;
                    return 0;
                }
                empty++;
            }
        }
    }
    else {
        for (ll i = 0; i < n; i++) {
            if (final_order_of_cows[i] == -1) {
                ll a, b, c, d;
                a = -1;
                b = -1;
                c = n;
                d = m;
                for (ll j = i - 1; j >= 0; j--) {
                    if (final_order_of_cows[j] != -1) {
                        if (cow_rel_pos.count(final_order_of_cows[j]) != 0) {
                            a = j;
                            b = cow_rel_pos[final_order_of_cows[j]];
                            break;
                        }
                    }
                }
                for (ll j = i + 1; j < n; j++) {
                    if (final_order_of_cows[j] != -1) {
                        if (cow_rel_pos.count(final_order_of_cows[j]) != 0) {
                            c = j;
                            d = cow_rel_pos[final_order_of_cows[j]];
                            break;
                        }
                    }
                }
                ll to_put = d - b - 1;
                ll empty_ct = 0;
                for (ll j = a + 1; j < c; j++) {
                    if (final_order_of_cows[j] == -1) {
                        empty_ct++;
                    }
                }
                if (empty_ct > to_put) {
                    cout << i + 1 << endl;
                    return 0;
                }
            }
        }
    }
}
