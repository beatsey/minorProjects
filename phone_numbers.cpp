#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;
char selectLetter(char l, set<char>& letters) {
    bool b = false;
    for (auto& c : letters) {
        if (b) {
            return c;
        }
        if (c == l) {
            b = true;
        }
        
    }
    return ' ';
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    set<char> letters;
    for (char l: s) {
        letters.insert(l);
    }
    if (k > n) {
        s.resize(k);
        for (int i = n; i < k; i++) {
            s[i] = *(letters.begin());
        }
        cout << s;
        return 0;
    }
    string t;
    int i;
    for (i = k - 1; i >= 0; i--) {
        if (s[i] != *(--letters.end())) {
            t = s.substr(0, i);
            t.resize(k);
            t[i] = selectLetter(s[i], letters);
            i++;
            break;
        }
    }
    for (; i < k; i++) {
        t[i] = *(letters.begin());
    }
    cout << t;
}