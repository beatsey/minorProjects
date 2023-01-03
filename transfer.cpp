#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<array<int, 3>>> graph;

int Dijkstra(int cups) {
    vector<bool> used(n+1);
    priority_queue <pair<int, int>> q;
    q.push(make_pair(0, -1));
    
    while (!q.empty()) {
        auto cur = q.top(); q.pop();
        int currentTime = -cur.first, from = -cur.second;
        used[from] = true;

        if (currentTime > 1440) {
            return 0;
        }

        if (from == n) {
            return currentTime;
        }

        for (auto road : graph[from]) {
            if (road[2] >= cups && !used[road[0]]) {
                int tmp = currentTime + road[1];
                if (tmp <= 1440) {
                    q.push(make_pair(-tmp, -road[0]));
                }
            }
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n+1);

    if (n == 1) {
        cout << 10000000 << endl;
        return 0;
    }

    set<int> uniqueCups;

    for (int i = 0; i < m; ++i) {
        int from, to, time, weight;
        cin >> from >> to >> time >> weight;
        int cups = (weight - 3000000) / 100;
        if (cups <= 0) {
            continue;
        }

        graph[from].push_back({to, time, cups});
        graph[to].push_back({from, time, cups});
        uniqueCups.insert(cups);
    }

    vector<int> uniqueCupsVec;
    for (auto cups : uniqueCups) {
        uniqueCupsVec.push_back(cups);
    }


    int l = 0;
    int r = uniqueCups.size() - 1;
    int maximumCups = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        int minTime = Dijkstra(uniqueCupsVec[m]);

        if (minTime == 0) {
            r = m - 1;
        } else {
            l = m + 1;

            if (uniqueCupsVec[m] > maximumCups) {
                maximumCups = uniqueCupsVec[m];
            }
        }
    }

    cout << maximumCups << endl;

    return 0;
}