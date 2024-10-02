#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int matrix[21][21];
bool visited[21][21] = { false, };
int dice[6] = { 1,5,3,4,2,6 };
//시계방향
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int N, M;
int total, cnt = 1;
void move_dice(int dir) {
    int ndice[6] = { 0, };
    switch (dir) {
    case 0: //동
        ndice[0] = dice[3];
        ndice[1] = dice[1];
        ndice[2] = dice[0];
        ndice[3] = dice[5];
        ndice[4] = dice[4];
        ndice[5] = dice[2];
        break;
    case 1: //남
        ndice[0] = dice[1];
        ndice[1] = dice[5];
        ndice[2] = dice[2];
        ndice[3] = dice[3];
        ndice[4] = dice[0];
        ndice[5] = dice[4];
        break;
    case 2: //서
        ndice[0] = dice[2];
        ndice[1] = dice[1];
        ndice[2] = dice[5];
        ndice[3] = dice[0];
        ndice[4] = dice[4];
        ndice[5] = dice[3];
        break;
    case 3: //북
        ndice[0] = dice[4];
        ndice[1] = dice[0];
        ndice[2] = dice[2];
        ndice[3] = dice[3];
        ndice[4] = dice[5];
        ndice[5] = dice[1];
        break;

    default:
        break;
    }
    for (int i = 0; i < 6; i++) {
        dice[i] = ndice[i];
    }
}
void dfs(int cy, int cx, int num) {
    visited[cy][cx] = true;
    for (int i = 0; i < 4; i++) {
        int ny = cy + dy[i];
        int nx = cx + dx[i];
        if (ny<1 || ny>N || nx<1 || nx>N) continue;
        if (visited[ny][nx] == true) continue;
        if (visited[ny][nx] == false && matrix[ny][nx] == num) {
            cnt += 1;
            dfs(ny, nx, num);
        }
    }
}
void solve(int cy, int cx, int cd) {
    //K만큼 반복
    while (M--) {
        int nd = cd;
        int ny = cy + dy[nd];
        int nx = cx + dx[nd];
        //방향이 없으면
        if (ny<1 || ny>N || nx<1 || nx>N) {
            nd = (nd + 2 + 4) % 4;
            ny = cy + dy[nd];
            nx = cx + dx[nd];
        }
        move_dice(nd);
        //점수 획득
        dfs(ny, nx, matrix[ny][nx]);
        total += (matrix[ny][nx] * cnt);
        cnt = 1;
        memset(visited, false, sizeof(visited));
        //이동 방향 결정
        if (dice[5] > matrix[ny][nx]) {
            nd = (nd + 1 + 4) % 4;
        }
        else if (dice[5] < matrix[ny][nx]) {
            nd = (nd - 1 + 4) % 4;
        }
        cy = ny, cx = nx, cd = nd;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            cin >> matrix[y][x];
        }
    }
    solve(1, 1, 0);
    cout << total;
    return 0;
}