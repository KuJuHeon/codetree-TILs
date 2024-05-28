#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;
struct ROBOT {
    int y, x, h, w, k, get;
    bool move;
};
//맵
int matrix[41][41];
int robot_map[41][41];
//변수
int L, N, q;
int main_i;
ROBOT robot[31];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
//함수
bool command(int i, int d) {
    int check = false;
    if (d == 0 || d == 2) {
        int sy;
        if (d == 0) sy = robot[i].y;
        else sy = robot[i].y + robot[i].h - 1;
        for (int x = robot[i].x; x < robot[i].x + robot[i].w; ++x) {
            int ny = sy + dy[d];
            int nx = x + dx[d];
            //격자 밖
            if (ny<1 || ny>L || nx < 1 || nx>L) {
                robot[i].move = false;
                return false;
            }
            //벽 만나면
            if (matrix[ny][nx] == 2) {
                robot[i].move = false;
                return false;
            }
            //빈칸이면
            if (robot_map[ny][nx] == 0) {
                robot[i].move = true;
                check = true;
                continue;
            }
            //다른 로봇 만나면
            if (robot_map[ny][nx] > 0) {
                check = command(robot_map[ny][nx], d);
                if (check == true) {
                    robot[i].move = true;
                    continue;
                }
                else {
                    robot[i].move = false;
                    return false;
                }
            }
        }
    }
    else if (d == 1 || d == 3) {
        int sx;
        if (d == 1) sx = robot[i].x + robot[i].w - 1;
        else sx = robot[i].x;
        for (int y = robot[i].y; y < robot[i].y + robot[i].h; ++y) {
            int ny = y + dy[d];
            int nx = sx + dx[d];
            //격자 밖
            if (ny<1 || ny>L || nx < 1 || nx>L) {
                robot[i].move = false;
                return false;
            }
            //벽 만나면
            if (matrix[ny][nx] == 2) {
                robot[i].move = false;
                return false;
            }
            //빈칸이면
            if (robot_map[ny][nx] == 0) {
                robot[i].move = true;
                check = true;
                continue;
            }
            //다른 로봇 만나면
            if (robot_map[ny][nx] > 0) {
                check = command(robot_map[ny][nx], d);
                if (check == true) {
                    robot[i].move = true;
                    continue;
                }
                else {
                    robot[i].move = false;
                    return false;
                }
            }
        }
    }
    return check;
}
void reset_move() {
    for (int i = 1; i <= N; ++i) {
        robot[i].move = false;
    }
}
void real_move(int i, int d, int candi[41][41]) {
    int num = robot_map[robot[i].y][robot[i].x];
    if (robot[i].move == true) {
        robot[i].y += dy[d];
        robot[i].x += dx[d];
    }
    for (int y = robot[i].y; y < robot[i].y + robot[i].h; ++y) {
        for (int x = robot[i].x; x < robot[i].x + robot[i].w; ++x) {
            candi[y][x] = num;
        }
    }
}
void move(int i, int d) {
    int candi[41][41] = { 0, };
    //죽은 애들은 제외하고
    for (int i = 1; i <= N; ++i) {
        if (robot[i].k == 0) continue;
        real_move(i, d, candi);
    }
    for (int y = 1; y <= L; ++y) {
        for (int x = 1; x <= L; ++x) {
            robot_map[y][x] = candi[y][x];
        }
    }
}
int get_trap(int i) {
    int sum = 0;
    //그 로봇 위치에 trap갯수 파악하기
    for (int y = robot[i].y; y < robot[i].y + robot[i].h; ++y) {
        for (int x = robot[i].x; x < robot[i].x + robot[i].w; ++x) {
            if (matrix[y][x] == 1) ++sum;
        }
    }
    return sum;
}
void erase(int i) {
    //해당 로봇 자리 0으로 만들기
    for (int y = robot[i].y; y < robot[i].y + robot[i].h; ++y) {
        for (int x = robot[i].x; x < robot[i].x + robot[i].w; ++x) {
            robot_map[y][x] = 0;
        }
    }
}
void check_trap() {
    for (int i = 1; i <= N; ++i) {
        if (robot[i].k == 0) continue;
        if (robot[i].move == false) continue;
        if (i == main_i) continue;
        int cnt = get_trap(i);
        robot[i].get += cnt;
        if (robot[i].get >= robot[i].k) {
            robot[i].k = 0;
            erase(i);
        }
    }
}
void solve(int i, int d) {
    //모든 움직임 초기화
    reset_move();
    //명령 받은 애부터 움직임 가능 여부 파악
    command(i, d);
    //맨 앞에가 못움직이면 움직임 초기화
    if (robot[main_i].move == false) reset_move();
    //실제 움직임
    move(i, d);
    //함정 위치 파악
    check_trap();
}
void make_robot_map() {
    for (int i = 1; i <= N; ++i) {
        for (int y = robot[i].y; y < robot[i].y + robot[i].h; ++y) {
            for (int x = robot[i].x; x < robot[i].x + robot[i].w; ++x) {
                robot_map[y][x] = i;
            }
        }
    }
}
int get_sum() {
    int sum = 0;
    //맵에 살아있는 애들만 총 받은 피해 더해줌
    for (int i = 1; i <= N; ++i) {
        if (robot[i].k == 0) continue;
        sum += robot[i].get;
    }
    return sum;
}
int main() {
    cin >> L >> N >> q;
    for (int y = 1; y <= L; ++y) {
        for (int x = 1; x <= L; ++x) {
            cin >> matrix[y][x];
        }
    }
    for (int i = 1; i <= N; ++i) {
        cin >> robot[i].y >> robot[i].x >> robot[i].h >> robot[i].w >> robot[i].k;
        robot[i].get = 0;
        robot[i].move = false;
    }
    memset(robot_map, 0, sizeof(robot_map));
    make_robot_map();
    while (q--) {
        int i, d;
        cin >> i >> d;
        if (robot[i].k == 0) continue;
        main_i = i;
        solve(i, d);
    }
    int result = get_sum();
    cout << result;
    return 0;
}