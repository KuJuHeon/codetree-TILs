#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
#define n 5
using namespace std;
int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };
int matrix[5][5], candi[5][5], MAX_m[5][5];
int wall[300], wall_idx;
bool visited[5][5];
int k, m;
int MAX_cnt = 0x80000000, MAX_y, MAX_x, MAX_dig;
vector<pair<int, int>>  MAX_v;
void show(int matrix[5][5]) {
    cout << "\n-----------------------------------------------\n";
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            cout << matrix[y][x] << " ";
        }
        cout << "\n";
    }
}
void copy(int matrix[5][5], int candi[5][5]) {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            candi[y][x] = matrix[y][x];
        }
    }
}
void dfs(int cy, int cx, int num, int &cnt, vector<pair<int, int>>& v) {
    ++cnt;
    visited[cy][cx] = true;
    v.push_back({ cy,cx });
    for (int i = 0; i < 4; ++i) {
        int ny = cy + dy[i];
        int nx = cx + dx[i];
        if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
        if (visited[ny][nx]) continue;
        else if (!visited[ny][nx] && candi[ny][nx] == num) dfs(ny, nx, num, cnt , v);
    }
}
//matrix 원본을 회전해서 candi에 넣고 candi로 dfs 조작
void rotate(int sy, int sx, int dig) {
    --sy, --sx;
    copy(matrix, candi);
    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 3; ++x) {
            if (dig == 0) candi[sy + x][sx + 3 - 1 - y] = matrix[sy + y][sx + x];
            else if (dig == 1) candi[sy + 3 - 1 - y][sx + 3 - 1 - x] = matrix[sy + y][sx + x];
            else if (dig == 2) candi[sy + 3 - 1 - x][sx + y] = matrix[sy + y][sx + x];
        }
    }
}
//이 함수로 최대의 경우를 찾는다.
void detect() {
    MAX_cnt = 0x80000000;
    for (int dig = 0; dig < 3; ++dig) {
        for (int x = 1; x <= 3; ++x) {
            for (int y = 1; y <= 3; ++y) {
                //우선 순위에 따라 탐색 진행
                //지금 셋팅으로 rotate해서 candi가 회전함
                rotate(y, x, dig);
                //여기서 얻어진 행렬로 dfs
                int sum = 0;
                vector<pair<int, int>> candi_v;
                memset(visited, false, sizeof(visited));
                for (int y = 0; y < n; ++y) {
                    for (int x = 0; x < n; ++x) {
                        //방문 안 한 곳이면 일단 dfs 시작
                        if (!visited[y][x]) {
                            int cnt = 0;
                            vector<pair<int, int>> v;
                            dfs(y, x, candi[y][x], cnt, v);
                            //찾은 구역이 3이상일 때만 
                            if (cnt >= 3) {
                                sum += cnt;
                                for (int i = 0; i < v.size(); ++i) candi_v.push_back(v[i]);
                            }
                        }
                    }
                }
                //여기서 얻은 게 더 크면 갱신
                if (MAX_cnt < sum) {
                    //cout << "갱신 " << sum << "\n";
                    MAX_y = y;
                    MAX_x = x;
                    MAX_dig = dig;
                    MAX_cnt = sum;
                    MAX_v = candi_v;
                    copy(candi, MAX_m);
                }
            }
        }
    }
}
//주어진 최대 정보들 실제 적용해서 벽면까지
void get() {
    for (int i = 0; i < MAX_v.size(); ++i) {
        int y = MAX_v[i].first;
        int x = MAX_v[i].second;
        MAX_m[y][x] = -1;
    }
    //cout << "--------연속된 숫자 제거한 거-------\n";
    //show(MAX_m);
    //이제 -1인 곳에 벽 채워넣기
    for (int x = 0; x < n; ++x) {
        for (int y = n - 1; y >= 0; --y) {
            if (MAX_m[y][x] == -1) {
                MAX_m[y][x] = wall[wall_idx++];
            }
        }
    }
    //이제 최대 적용한 행렬이 진짜가 됨.
    copy(MAX_m, matrix);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k >> m;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            cin >> matrix[y][x];
        }
    }
    for (int i = 0; i < m; ++i) cin >> wall[i];

    //k턴만큼 한다
    for(int i = 0; i < k; ++i) {
        //cout << "----------------" << i+1 << "번째 진행 중---------------\n";
        int ret = 0;
        //탐색 시작, 언제가 최대의 셋팅인지 정함
        detect();
        //만약에 이번 판에 되는 유물 못찾았으면 k_check = false하고 break;
        if (MAX_cnt <= 0) break;
        ret += MAX_cnt;
        //이 아래로 갈 수 있으면 그 판은 일단 진행 가능
        while (1) {
            //찾은 거로 찐 적용ㄱㄱ
            get();       
            //cout << "----------제거한 결과-------\n";
            //show(matrix);
            //적용하고 나서 다시 연쇄 확인
            //여기서 얻어진 행렬로 dfs
            int sum = 0;
            MAX_cnt = 0x80000000;
            vector<pair<int, int>> candi_v;
            memset(visited, false, sizeof(visited));
            copy(matrix, candi);
            for (int y = 0; y < n; ++y) {
                for (int x = 0; x < n; ++x) {
                    //방문 안 한 곳이면 일단 dfs 시작
                    if (!visited[y][x]) {
                        int cnt = 0;
                        vector<pair<int, int>> v;
                        dfs(y, x, candi[y][x], cnt, v);
                        //찾은 구역이 3이상일 때만 
                        if (cnt >= 3) {
                            sum += cnt;
                            for (int i = 0; i < v.size(); ++i) candi_v.push_back(v[i]);
                        }
                    }
                }
            }
            //여기서 얻은 게 더 크면 갱신
            if (MAX_cnt < sum) {
                //cout << "갱신 " << sum << "\n";
                MAX_cnt = sum;
                MAX_v = candi_v;
            }
            //연쇄 안되면 빠져나가기
            if (MAX_cnt <= 0) break;
            //cout << "----------------연쇄 반응 됨--------------\n";
            ret += MAX_cnt;
        }
        //탐색한 초대 보물 갯수 출력
        cout << ret << " ";
    }

    return 0;
}