#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int n, m, q;
int matrix[100][100];
int dy[4] = { 0,0,1,-1 };
int dx[4] = { -1,1,0,0 };
void wind(int r1, int c1, int r2, int c2) {
    int temp = matrix[r1][c1];
    for (int y = r1 + 1; y <= r2; ++y) matrix[y - 1][c1] = matrix[y][c1];
    for (int x = c1 + 1; x <= c2; ++x) matrix[r2][x - 1] = matrix[r2][x];
    for (int y = r2 - 1; y >= r1; --y) matrix[y + 1][c2] = matrix[y][c2];
    for (int x = c2 - 1; x >= c1 + 1; --x) matrix[r1][x + 1] = matrix[r1][x];
    matrix[r1][c1 + 1] = temp;
}
void avg(int r1, int c1, int r2, int c2) {
    int candi[100][100];
    for (int y = r1; y <= r2; ++y) {
        for (int x = c1; x <= c2; ++x) {
            int sum = matrix[y][x];
            int cnt = 1;
            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
                cnt++; //갯수 세기
                sum += matrix[ny][nx]; //합 더하기
            }
            sum /= cnt;
            candi[y][x] = sum;
        }
    }
    //다 하고 복사
    for (int y = r1; y <= r2; ++y) {
        for (int x = c1; x <= c2; ++x) {
            matrix[y][x] = candi[y][x];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            cin >> matrix[y][x];
        }
    }
    int r1, c1, r2, c2;
    while (q--) {
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; r2--; c1--; c2--;
        wind(r1, c1, r2, c2);
        avg(r1, c1, r2, c2);
    }
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            cout << matrix[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}