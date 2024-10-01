#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int n, m, q;
int matrix[100][100];
bool check(int st, int target) {
    for (int x = 0; x < m; ++x) {
        if (matrix[st][x] == matrix[target][x]) return true;
    }
    return false;
}
void wind(int y, int dir) {
    //왼쪽에서 불어온다
    if (dir == -1) {
        int temp = matrix[y][m - 1];
        for (int x = m - 2; x >= 0; --x) matrix[y][x + 1] = matrix[y][x];
        matrix[y][0] = temp;
    }
    //오른쪽에서 불어온다
    else {
        int temp = matrix[y][0];
        for (int x = 1; x < m; ++x) matrix[y][x - 1] = matrix[y][x];
        matrix[y][m - 1] = temp;
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
    while (q--) {
        int Y, wind_dir;
        char D;
        cin >> Y >> D;
        --Y;
        //바람에 따른 방향 정하기
        if (D == 'L') wind_dir = -1;
        else wind_dir = 1;
        //일단 여기 바람 날리고
        wind(Y, wind_dir);
        //그 밑으로 전파
        int dir = wind_dir * -1;
        for (int y = Y - 1; y >= 0; --y) {
            //만약에 전파가 불가능이면 바로 나오기
            //y+1을 기준으로 y가 전파 받는지
            if (!check(y + 1, y)) break;
            wind(y, dir);
            dir *= -1;

        }
        dir = wind_dir * -1;
        for (int y = Y + 1; y < n; ++y) {
            if (!check(y - 1, y)) break;
            wind(y, dir);
            dir *= -1;
        }
    }
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            cout << matrix[y][x] << " ";
        }
        cout << "\n";
    }
    return 0;
}