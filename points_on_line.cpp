#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int  i = 0, j = 0;
    int mx = 1;
    for (; i < nums.size(); i++) {
        if (nums[i] - nums[j] <= d) {
            mx = max(mx, i - j + 1);
        }
        for (; nums[i] - nums[j] > d; j++);
    }
    cout << nums.size() - mx;
}