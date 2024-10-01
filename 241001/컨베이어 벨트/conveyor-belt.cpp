#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int matrix[2][200], candi[2][200];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, t;
    cin >> n >> t;
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < n; ++x) {
            cin >> matrix[y][x];
        }
    }
    int move_x = t % n;
    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < n; ++x) {
            int move_y = t / n;
            int nx = (x + move_x + n) % n;
            move_y += (x + move_x) / n;
            int ny = (y + move_y + 2) % 2;
            
            candi[ny][nx] = matrix[y][x];
        }
    }

    for (int y = 0; y < 2; ++y) {
        for (int x = 0; x < n; ++x) {
            cout << candi[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}