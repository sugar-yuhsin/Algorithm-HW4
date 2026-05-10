// Random TSP instance generator.
// Usage: ./gen_data <n> <seed> > out.txt
#include <iostream>
#include <random>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <n> <seed>\n";
        return 1;
    }
    int n = atoi(argv[1]);
    unsigned int seed = (unsigned int)atoi(argv[2]);
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(1, 9999);

    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) cout << 10000;
            else        cout << dist(rng);
            if (j + 1 < n) cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
