#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;
struct SANTA {
    int y, x, score, stun;
};
//맵
int matrix[51][51];
//변수
int dy[8] = { -1,0,1,0,1,1,-1,-1 };
int dx[8] = { 0,1,0,-1,1,-1,1,-1 };
int N, M, P, C, D, ret;
int r_y, r_x;
SANTA santa[31];
//함수
void print_score() {
    for (int i = 1; i <= P; ++i) {
        cout << santa[i].score << " ";
    }
    cout << "\n";
}
int get_santa_dis() {
    int MIN = 0x7fffffff;
    int MIN_santa = 0;
    //가장 가까운 산타 고르기
    for (int i = 1; i <= P; ++i) {
        if (santa[i].y == -1) continue;
        int dis = abs(r_y - santa[i].y) * abs(r_y - santa[i].y) + abs(r_x - santa[i].x) * abs(r_x - santa[i].x);
        if (MIN > dis) {
            MIN = dis;
            MIN_santa = i;
        }
        else if (MIN == dis) {
            if (santa[MIN_santa].y < santa[i].y || (santa[MIN_santa].y == santa[i].y && santa[MIN_santa].x < santa[i].x)) {
                MIN = dis;
                MIN_santa = i;
            }
        }
    }
    //가장 가까운 산타 방향 찾기
    int origin_dis = abs(r_y - santa[MIN_santa].y) * abs(r_y - santa[MIN_santa].y) + abs(r_x - santa[MIN_santa].x) * abs(r_x - santa[MIN_santa].x);
    MIN = 0x7fffffff;
    int MIN_dir = 0;
    for (int d = 0; d < 8; ++d) {
        int ny = r_y + dy[d];
        int nx = r_x + dx[d];
        if (ny<1 || ny>N || nx<1 || nx>N) continue;
        int dis = abs(santa[MIN_santa].y - ny) * abs(santa[MIN_santa].y - ny) + abs(santa[MIN_santa].x - nx) * abs(santa[MIN_santa].x - nx);
        if (dis > origin_dis) continue;
        if (dis < MIN) {
            MIN = dis;
            MIN_dir = d;
        }
    }
    return MIN_dir;
}
bool move_rudolf(int dir) {
    matrix[r_y][r_x] = 0;
    //그 쪽 방향으로 1칸 움직이기
    r_y += dy[dir];
    r_x += dx[dir];
    //산타가 있으면
    if (matrix[r_y][r_x] > 0) return true;
    else return false;
}
void push_santa(int num, int dir, int type, bool is_first) {
    if (is_first) {
        santa[num].y += type * dy[dir];
        santa[num].x += type * dx[dir];
        santa[num].score += type;
        santa[num].stun = 2;
    }
    else {
        santa[num].y += dy[dir];
        santa[num].x += dx[dir];
    }
    int y = santa[num].y;
    int x = santa[num].x;
    //격자 밖이면 밀려나서 죽음
    if (santa[num].y < 1 || santa[num].y > N || santa[num].x < 1 || santa[num].x > N) {
        santa[num].y = -1;
        return;
    }
    //다른 산타 있으면 그 산타 밀고
    if (matrix[y][x] > 0) {
        push_santa(matrix[y][x], dir, type, false);
    }
    matrix[y][x] = num;
    
}
void move_santa() {
    for (int i = 1; i <= P; ++i) {
        //격자 아웃 or 스턴은 안움직임
        if (santa[i].y == -1 || santa[i].stun > 0) continue;
        //산타까지 어느 방향으로 가야하는지
        int MIN = 0x7fffffff;
        int MIN_dir = 0;
        int origin_dis= abs(r_y - santa[i].y) * abs(r_y - santa[i].y) + abs(r_x - santa[i].x) * abs(r_x - santa[i].x);
        for (int d = 0; d < 4; ++d) {
            int ny = santa[i].y + dy[d];
            int nx = santa[i].x + dx[d];
            if (ny<1 || ny>N || nx<1 || nx>N) continue;
            int dis = abs(r_y - ny) * abs(r_y - ny) + abs(r_x - nx) * abs(r_x - nx);
            //산타 있으면 못 감
            if (matrix[ny][nx] > 0) continue;
            //가까워지지 않으면 안됨
            if (dis >= origin_dis) continue;        
            if (dis < MIN) {
                MIN = dis;
                MIN_dir = d;
            }
        }
        //갱신이 안됐다->움직일 수 있는 방향이 없다
        if (MIN == 0x7fffffff) continue;
        //얻은 방향으로 가보자
        int ny = santa[i].y + dy[MIN_dir];
        int nx = santa[i].x + dx[MIN_dir];
        //그냥 빈 공간이면 이동하고 좌표 갱신
        if (matrix[ny][nx] == 0) {
            matrix[ny][nx] = i;
            matrix[santa[i].y][santa[i].x] = 0;
            santa[i].y = ny, santa[i].x = nx;
        }
        //루돌프 있으면
        else if (matrix[ny][nx] == -1) {
            //원래 자리 0만들어 주기
            matrix[santa[i].y][santa[i].x] = 0;
            santa[i].y = ny, santa[i].x = nx;
            int new_dir = (MIN_dir + 2 + 4) % 4;
            push_santa(i, new_dir, D, true);
        }
    }
}
void plus_minus() {
    for (int i = 1; i <= P; ++i) {
        if (santa[i].y == -1) continue;
        santa[i].score += 1;
        if (santa[i].stun > 0) --santa[i].stun;
    }
}
bool is_all_die() {
    for (int i = 1; i <= P; ++i) {
        //-1이 아니면 살아있는 애가 있으므로 바로 false리턴
        if (santa[i].y != -1) return false;
    }
    return true;
}
void solve() {
    for (int i = 0; i < M; ++i) {
        //1.루돌프 움직이기
        //산타까지 거리 구하기(어느 방향으로 이동하는지
        int dir = get_santa_dis();
        //루돌프 움직이기(움직이고 마지막에 루돌프 자리 생신)
        bool check = move_rudolf(dir);
        //산타 있으면 밀려나기
        if (check) push_santa(matrix[r_y][r_x], dir, C, true);
        matrix[r_y][r_x] = -1;
        //2.산타 움직이기
        move_santa();
        //마지막에 살아있는 애들 점수+1하고 스턴 -1
        plus_minus();
        if (is_all_die()) break;
    }
    //마지막에 점수 출력
    print_score();
}
int main() {
    cin >> N >> M >> P >> C >> D;
    cin >> r_y >> r_x;
    matrix[r_y][r_x] = -1;
    for (int i = 0; i < P; ++i) {
        int num, y, x;
        cin >> num >> y >> x;
        santa[num].y = y, santa[num].x = x;
        matrix[y][x] = num;
    }
    solve();
    return 0;
}