#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int matrix[3][200], candi[3][200];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t, m = 3;
    cin >> n >> t;
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            cin >> matrix[y][x];
        }
    }
    int move_x = t % n;
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            int move_y = ((x + t) / n) % m;
            int ny = (y + move_y + m) % m;
            int nx = (x + move_x + n) % n;
            candi[ny][nx] = matrix[y][x];
        }
    }

    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            cout << candi[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}