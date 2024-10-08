#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <queue>
#include <cstring>
using namespace std;
int matrix[73][70];
bool visited[73][70];
int r, c, k;
int dy[5] = { -1,0,1,0,0 };
int dx[5] = { 0,1,0,-1,0 };
struct ANGEL {
    int y, x, ex;
    ANGEL() {
        y = 1; x = 0; ex = 0;
    }
};
ANGEL angel[1001];
bool find_south(int num) {
    int s_dy[3] = { 1,1,2 };
    int s_dx[3] = { -1,1,0 };

    int y = angel[num].y;
    int x = angel[num].x;
    for (int i = 0; i < 3; ++i) {
        int ny = y + s_dy[i];
        int nx = x + s_dx[i];
        if (ny < 0 || ny >= r || nx < 0 || nx >= c) return false;
        if (matrix[ny][nx] != 0) return false;
    }
    return true;
}
void move_south(int num) {
    int ddy[5] = { 0,2,1,1,1 };
    int ddx[5] = { 0,0,-1,1,0 };

    //기존 자리 없애기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + dy[i];
        int nx = angel[num].x + dx[i];
        matrix[ny][nx] = 0;
    }
    //신규 자리 옮기기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + ddy[i];
        int nx = angel[num].x + ddx[i];
        matrix[ny][nx] = num;
    }
    //정보 바꾸기
    angel[num].y = angel[num].y + ddy[4];
    angel[num].x = angel[num].x + ddx[4];
}
bool find_west(int num) {
    int dy[5] = { 0,-1,1,1,2 };
    int dx[5] = { -2,-1,-1,-2,-1 };

    int y = angel[num].y;
    int x = angel[num].x;
    for (int i = 0; i < 5; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || ny >= r || nx < 0 || nx >= c) return false;
        if (matrix[ny][nx] != 0) return false;
    }
    return true;
}
void move_west(int num) {
    int ddy[5] = { 0,1,1,2,1 };
    int ddx[5] = { -1,0,-2,-1,-1 };

    //기존 자리 없애기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + dy[i];
        int nx = angel[num].x + dx[i];
        matrix[ny][nx] = 0;
    }
    //신규 자리 옮기기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + ddy[i];
        int nx = angel[num].x + ddx[i];
        matrix[ny][nx] = num;
    }
    //출구 바꾸기
    angel[num].y = angel[num].y + ddy[4];
    angel[num].x = angel[num].x + ddx[4];
    angel[num].ex = (angel[num].ex - 1 + 4) % 4;
}
bool find_east(int num) {
    int dy[5] = { 0,1,-1,2,1 };
    int dx[5] = { 2,1,1,1,2 };

    int y = angel[num].y;
    int x = angel[num].x;
    for (int i = 0; i < 5; ++i) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny < 0 || ny >= r || nx < 0 || nx >= c) return false;
        if (matrix[ny][nx] != 0) return false;
    }
    return true;
}
void move_east(int num) {
    int ddy[5] = { 0,1,2,1,1 };
    int ddx[5] = { 1,0,1,2,1 };

    //기존 자리 없애기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + dy[i];
        int nx = angel[num].x + dx[i];
        matrix[ny][nx] = 0;
    }
    //신규 자리 옮기기
    for (int i = 0; i < 5; ++i) {
        int ny = angel[num].y + ddy[i];
        int nx = angel[num].x + ddx[i];
        matrix[ny][nx] = num;
    }
    //출구 바꾸기, 정보 바꾸기
    angel[num].y = angel[num].y + ddy[4];
    angel[num].x = angel[num].x + ddx[4];
    angel[num].ex = (angel[num].ex + 1 + 4) % 4;
}
bool is_exit(int y, int x, int num) {
    int ed = angel[num].ex;
    int e_y = angel[num].y + dy[ed];
    int e_x = angel[num].x + dx[ed];

    //내 위치가 출구랑 같으면 true
    if (y == e_y && x == e_x) {
        return true;
    }
    return false;
}
int bfs(int num) {
    int y = angel[num].y;
    int x = angel[num].x;
    int MAX_Y = y;
    visited[y][x] = true;
    queue<pair<int, int>> q;
    q.push({ y,x });
    while (!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        int cnum = matrix[cy][cx];
        bool check = is_exit(cy, cx, cnum);
        q.pop();
        //가장 아래로 간 행 고르기
        if (cy > MAX_Y) {
            MAX_Y = cy;
            //맨 끝에가 이미 나왔으면 더 볼 필요 없다.
            if (MAX_Y == r - 1) {
                break;
            }
        }
        for (int i = 0; i < 4; ++i) {
            int ny = cy + dy[i];
            int nx = cx + dx[i];
            if (ny < 0 || ny >= r || nx < 0 || nx >= c) {
                continue;
            }
            if (visited[ny][nx] || matrix[ny][nx] == 0) {
                continue;
            }
            //현재 내 위치가 출구면 주변 담을 수 있는 거 다 담아
            if (!visited[ny][nx] && check && matrix[ny][nx] != 0) {
                visited[ny][nx] = true;
                q.push({ ny,nx });
            }
            //내가 출구가 아니면 같은 애들만 담아
            else if (!visited[ny][nx] && !check && matrix[ny][nx] == cnum) {
                visited[ny][nx] = true;
                q.push({ ny,nx });
            }
        }
    }

    return MAX_Y;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> c >> k;
    r += 3;
    //k개의 정령이 골렘 타고 내려온다.
    int ret = 0;
    for(int i = 1; i <= k; ++i) {
        int c, d;
        cin >> c >> d;
        --c;
        angel[i].x = c;
        angel[i].ex = d;
        //주어진 골렘 이동시키자.
        while (1) {
            if (find_south(i)) {
                move_south(i);
            }
            else if (find_west(i)) {
                move_west(i);
            }
            else if (find_east(i)) {
                move_east(i);
            }
            else break;
        }
        //이건 
        if (angel[i].y < 4) {
            //맵 비우기
            memset(matrix, 0, sizeof(matrix));
            memset(visited, false, sizeof(visited));
            continue;
        }
        //안넘쳤으면
        else {
            //탈출 시작
            memset(visited, false, sizeof(visited));
            int val = bfs(i);
            ret += (val-2);
        }

    }
    cout << ret;
    return 0;
}