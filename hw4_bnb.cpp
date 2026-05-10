#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <ctime>

using namespace std;

static int n;
static vector<vector<int>> C;
static vector<int> minOut;
static int bestCost;
static vector<int> bestPath;
static vector<int> curPath;
static vector<bool> visited;

static void dfs(int cur, int depth, int cost, int remMin) {
    if (depth == n) {
        int total = cost + C[cur][0];
        if (total < bestCost) {
            bestCost = total;
            bestPath = curPath;
        }
        return;
    }

    int newRemMin = remMin - minOut[cur];

    vector<pair<int,int>> cand;
    cand.reserve(n);
    for (int next = 0; next < n; ++next) {
        if (!visited[next]) cand.push_back({C[cur][next], next});
    }
    sort(cand.begin(), cand.end());

    for (auto &p : cand) {
        int edge = p.first;
        int next = p.second;
        int newCost = cost + edge;
        if (newCost + newRemMin >= bestCost) break;
        visited[next] = true;
        curPath.push_back(next);
        dfs(next, depth + 1, newCost, newRemMin);
        curPath.pop_back();
        visited[next] = false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    C.assign(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> C[i][j];

    if (n == 1) {
        cout << "The shortest Hamiltonian cycle:\n1 1\nTotal cost: 0\nTime: 0.000000\n";
        return 0;
    }

    // 找每個 row 最小的
    minOut.assign(n, INT_MAX);
    int totalMin = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (i != j && C[i][j] < minOut[i]) minOut[i] = C[i][j];
        totalMin += minOut[i];
    }

    bestCost = INT_MAX;
    {
        vector<bool> v(n, false);
        v[0] = true;
        vector<int> path = {0};
        int cur = 0, total = 0;
        for (int k = 1; k < n; ++k) {
            int bn = -1, bc = INT_MAX;
            for (int j = 0; j < n; ++j)
                if (!v[j] && C[cur][j] < bc) { bc = C[cur][j]; bn = j; }
            v[bn] = true;
            path.push_back(bn);
            total += bc;
            cur = bn;
        }
        total += C[cur][0];
        bestCost = total;
        bestPath = path;
    }

    visited.assign(n, false);
    visited[0] = true;
    curPath.clear();
    curPath.push_back(0);

    clock_t t0 = clock();
    dfs(0, 1, 0, totalMin);
    clock_t t1 = clock();

    cout << "The shortest Hamiltonian cycle:\n";
    for (int v : bestPath) cout << v + 1 << ' ';
    cout << "1\n";
    cout << "Total cost: " << bestCost << '\n';
    cout.setf(std::ios::fixed); cout.precision(6);
    cout << "Time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << '\n';

    return 0;
}
