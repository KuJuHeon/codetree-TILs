#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

struct BOX {
    int idx;
    int weight;
    int belt;
};
struct BELT {
    bool is_broken;
    list<BOX> B;
};
int q, cmd, n, m;
BOX box[100000];
BELT belt[10];
unordered_map<int, list<BOX>::iterator> box_map;
bool is_belt_empty(int belt_num) {
    return (belt[belt_num].B.begin() == belt[belt_num].B.end());
}
void show() {
    for (int i = 0; i < m; ++i) {
        cout << i + 1 << "벨트 ";
        for (list<BOX>::iterator iter = belt[i].B.begin(); iter != belt[i].B.end(); ++iter) {
            cout << iter->idx << " ";
        }
        cout << "\n";
    }
}
void q_100() {
    //박스 갯수, 벨트 갯수 입력 받기
    cin >> n >> m;
    int id[100000], w[100000];
    //박스 id랑 무게 받기
    for (int i = 0; i < n; ++i) cin >> id[i];
    for (int i = 0; i < n; ++i) cin >> w[i];

    //벨트에 차례대로 넣기
    int pos = 0;
    for (int belt_num = 0; belt_num < m; ++belt_num) {
        //갯수에 맞게 넣기
        for (int i = 0; i < n / m; ++i) {
            box[pos].idx = id[pos];
            box[pos].weight = w[pos];
            box[pos].belt = belt_num;
            //이 정보에 해당하면 박스를 벨트 위에 올리자
            belt[belt_num].B.push_back(box[pos]);
            list<BOX>::iterator it = --belt[belt_num].B.end();
            box_map.insert({ box[pos].idx,it });
            ++pos;
        }
    }
}
int q_200() {
    int ret = 0;
    int w;
    cin >> w;
    //벨트 앞부분 상자 무게 확인
    for (int i = 0; i < m; ++i) {
        //만약에 비어있거나 고장난 벨트라면 패스
        if (is_belt_empty(i) || belt[i].is_broken) {
            //cout << "고장나서 패스\n";
            continue;
        }
        list<BOX>::iterator iter = belt[i].B.begin();
        //이하면 하차하고 무게 더하자, 그리고 박스 삭제까지
        if (iter->weight <= w) {
            //cout << "안넘어서 무게 더하고 삭제\n";
            ret += iter->weight;
            box_map.erase(iter->idx);
            belt[i].B.erase(iter);            
        }
        else {
            //erase를 하면 메모리에서 해제가 돼서 이렇게 해줘야 한다.
            //cout << "넘어서 바로 삭제\n";
            BOX candi = *iter;  
            belt[i].B.push_back(candi);
            box_map[iter->idx] = --belt[i].B.end();
            belt[i].B.erase(iter);        
        }
        
    }
    return ret;
}
int q_300() {
    //id를 받아서 그 아이디 있으면 제거하고 한 칸씩 떙긴다
    int id;
    //cout << 999990 << "\n";
    cin >> id;
    //cout << 999991 << "\n";
    //없으면 -1 리턴
    if (box_map.find(id) == box_map.end()) {
        //cout << 999992 << "\n";
        return -1;
    }
    //일단 그 박스의 위치를 파아
    //cout << 999997 << "\n";
    list<BOX>::iterator iter = box_map[id];
    //cout << 999998 << "\n";
    //그 박스가 어느 벨트인지 파악
    int idx = iter->belt;
    //cout << 999996 << "\n";
    //그 벨트에서 박스 지워줘
    belt[idx].B.erase(iter);
    //cout << 999993 << "\n";
    //맵에서도 지워
    box_map.erase(id);
    //cout << 999994 << "\n";
    return id;
}
int q_400() {
    //id를 받아서 그 아이디 있으면 모든 상자를 전부 앞으로 가지고 온다.
    int id;
    cin >> id;
    //없으면 -1 리턴
    //cout << 999990 << "\n";
    if (box_map.find(id) == box_map.end()) {
        return -1;
    }
    //이 위치부터 끝까지를 앞으로 가져오자
    //cout << 999991 << "\n";
    list<BOX>::iterator iter = box_map[id];
    int idx = iter->belt;
    //cout << "이 박스의 벨트 번호 " << idx + 1 << "\n";
    //근데 원래 맨 앞에 있던 상자면 아래를 할 필요가 없다.
    //cout << 999992 << "\n";
    if (iter != belt[idx].B.begin()) {
        //cout << 999994 << "\n";
        //그 위치부터 끝까지 반복문->목표는 맨 뒤에서부터 그 위치까지 하나씩 앞으로 땡긴다.
        //이때 for문을 이용하기 위해서 그 위치 한 칸 앞에 있는 애가 되기 전까지 반복문을 돌린다.
        list<BOX>::iterator target = iter;
        --target;
        //cout << 999993 << "\n";
        for (iter = --belt[idx].B.end(); iter != target;) {
            BOX candi = *iter;
            //앞에서부터 집어넣고
            belt[idx].B.push_front(candi);
            //해시 다시 조정해주고
            box_map[candi.idx] = belt[idx].B.begin();
            //앞에다가 추가했으면 뒤에 있던 건 지워주자
            belt[idx].B.erase(iter);
            iter = --belt[idx].B.end();
        }
    }
    //cout << 999999 << "\n";
    return idx + 1;
}
int q_500() {
    int belt_num;
    cin >> belt_num;
    --belt_num;

    //이미 고장 났으면 -1 리턴
    if (belt[belt_num].is_broken) return -1;
    //여긴 안고장났으니까 고장난거로 바꿔줘
    belt[belt_num].is_broken = true;
    //비어있지 않은 벨트만 해주면 됨
    if (!is_belt_empty(belt_num)) {
        int target = (belt_num + 1) % m;
        //오른쪽부터 돌면서 안고장난 벨트 찾기
        while (belt[target].is_broken) {
            target = (target + 1) % m;
        }
        //여기서부터 target은 안고장난 벨트의 idx임
        list<BOX>::iterator iter;
        for (iter = belt[belt_num].B.begin(); iter != belt[belt_num].B.end(); ) {
            iter->belt = target;
            //타겟 벨트에 원소 하나 넣고
            belt[target].B.push_back(*iter);
            //이제 이 박스는 target 벨트로 옮겨진다.           
            //cout << "옮겨갈 벨트 번호 " << target + 1 << "\n";
            //그 원소 id뭔지 알아내고
            int idx = iter->idx;
            //해시에 위치 새롭게 갱신
            box_map[idx] = --belt[target].B.end();
            //그 벨트에서도 그냥 지워주자
            iter = belt[belt_num].B.erase(iter);        
        }
    }
    return belt_num + 1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> q;
    while (q--) {
        cin >> cmd;
        switch (cmd) {
        case 100:
            q_100();
            //show();
            break;
        case 200:
            cout << q_200() << "\n";
            //show();
            break;
        case 300:
            cout << q_300() << "\n";
            //show();
            break;
        case 400:
            cout << q_400() << "\n";
            //show();
            break;
        case 500:
            cout << q_500() << "\n";
            //show();
            break;
        }
    }
    return 0;
}