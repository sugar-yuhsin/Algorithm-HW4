#include <iostream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

static int n;
static vector<vector<int>> C;
static int bestCost;
static vector<int> bestPath;
static vector<int> curPath;
static vector<bool> visited;

static void dfs(int cur, int depth, int cost) {
    if (depth == n) {
        int total = cost + C[cur][0];
        if (total < bestCost) {
            bestCost = total;
            bestPath = curPath;
        }
        return;
    }
    for (int next = 0; next < n; ++next) {
        if (!visited[next]) {
            visited[next] = true;
            curPath.push_back(next);
            dfs(next, depth + 1, cost + C[cur][next]);
            curPath.pop_back();
            visited[next] = false;
        }
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

    bestCost = INT_MAX;
    visited.assign(n, false);
    visited[0] = true;
    curPath.clear();
    curPath.push_back(0);

    clock_t t0 = clock();
    dfs(0, 1, 0);
    clock_t t1 = clock();

    cout << "The shortest Hamiltonian cycle:\n";
    for (int v : bestPath) cout << v + 1 << ' ';
    cout << "1\n";
    cout << "Total cost: " << bestCost << '\n';
    cout.setf(std::ios::fixed); cout.precision(6);
    cout << "Time: " << (double)(t1 - t0) / CLOCKS_PER_SEC << '\n';

    return 0;
}
