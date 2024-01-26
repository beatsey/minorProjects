#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int l_max = -1e9;
    int r_min = 1e9;
    int n;
    cin >> n;
    vector<int> a(n);
    string b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> b;
    for (int i = 4; i < n; i++) {
        if (b[i - 1] != b[i - 2] || b[i - 2] != b[i - 3] || b[i - 3] != b[i - 4])
            continue;
        if (b[i] == b[i - 1])
            continue;
        if (b[i] == '1') {
            l_max = max(*max_element(a.begin() + i - 4, a.begin() + i + 1) + 1, l_max);
            
        }
        else {
            r_min = min(*min_element(a.begin() + i - 4, a.begin() + i + 1) - 1, r_min);
        }
    }
    cout << l_max << " " << r_min;
}