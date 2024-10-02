#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int n;
int r, c, m1, m2, m3, m4, dir;
int matrix[100][100];
void four(int y, int x, int cnt) {
    if (cnt == m2) return;
    matrix[y + 1][x + 1] = matrix[y][x];
    four(y - 1, x - 1, cnt + 1);
}
void three(int y, int x, int cnt) {
    if (cnt == m1) return;
    matrix[y + 1][x - 1] = matrix[y][x];
    three(y - 1, x + 1, cnt + 1);
}
void two(int y, int x, int cnt) {
    if (cnt == m2) return;
    matrix[y - 1][x - 1] = matrix[y][x];
    two(y + 1, x + 1, cnt + 1);
}
void one(int y, int x, int cnt) {
    if (cnt == m1 - 1) return;
    matrix[y - 1][x + 1] = matrix[y][x];
    one(y + 1, x - 1, cnt + 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            cin >> matrix[y][x];
        }
    }
    
    cin >> r >> c >> m1 >> m2 >> m3 >> m4 >> dir;
    --r, --c;
    //반시계
    if (dir == 0) {
        int temp = matrix[r][c];
        int y, x;

        y = r, x = c;
        four(y - 1, x - 1, 0);

        y = r - m2, x = c - m2;
        three(y - 1, x + 1, 0);

        y = r - m2 - m1, x = c - m2 + m1;
        two(y + 1, x + 1, 0);

        y = r - m1, x = c + m1;
        one(y + 1, x - 1, 0);

        matrix[r - 1][c + 1] = temp;
    }
    //시계
    else {
        int temp = matrix[r][c];
        int y, x;

        y = r, x = c;
        three(y - 1, x + 1, 0);

        y = r - m1, x = c + m1;
        four(y - 1, x - 1, 0);

        y = r - m2 - m1, x = c - m2 + m1;
        one(y + 1, x - 1, 0);

        y = r - m2, x = c - m2;
        two(y + 1, x + 1, 0);
        matrix[r - 1][c - 1] = temp;
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            cout << matrix[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}