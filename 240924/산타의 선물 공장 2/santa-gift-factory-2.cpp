#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <unordered_map>
using namespace std;
struct BOX {
    int idx;
    BOX* prev;
    BOX* next;

    BOX() {
        prev = NULL;
        next = NULL;
    }
};
struct BELT {
    int count;
    BOX* head;
    BOX* tail;
    BELT() {
        count = 0;
        head = new BOX();
        tail = new BOX();

        head->next = tail;
        tail->prev = head;

        head->prev = NULL;
        tail->next = NULL;
    }
};
int q, cmd, n, m;
unordered_map<int, BOX*> box_map;
BOX box[100000];
BELT belt[100000];
bool empty(int belt_num) {
    return (belt[belt_num].count == 0);
}
//원소를 맨 뒤에 넣는 함수
void push_back(int belt_num, BOX* B) {
    box_map[B->idx] = B;
    BOX* prev = belt[belt_num].tail->prev;
    BOX* next = belt[belt_num].tail;

    //기준 양 연결 시키고
    B->prev = prev;
    B->next = next;
    //기존 것들 연결 수정하고
    prev->next = B;
    next->prev = B;
    //넣을 때마다 갯수 하나씩 증가
    ++belt[belt_num].count;
}
void q_100() {
    cin >> n >> m;
    int belt_num;
    for (int i = 0; i < m; ++i) {
        cin >> belt_num;
        --belt_num;

        box[i].idx = i;
        push_back(belt_num, &box[i]);
    }
}
//src의 상자 from부터 to까지 count개를 dst의 맨 앞으로 옮기는 함수
void move(int dst, int src, BOX* from, BOX* to, int count) {
    BOX* fprev = from->prev;
    BOX* tnext = to->next;

    BOX* prev = belt[dst].head;
    BOX* next = belt[dst].head->next;

    //src head와 tail을 이어줌
    fprev->next = tnext;
    tnext->prev = fprev;

    //src 본체 옮기기
    from->prev = prev;
    to->next = next;

    //기존 dst 조절하기
    prev->next = from;
    next->prev = to;

    belt[dst].count += count;
    belt[src].count -= count;
}
int q_200() {
    int src, dst;
    cin >> src >> dst;
    src--, dst--;
    int cnt = belt[src].count;
    if (cnt > 0) {
        BOX* from = belt[src].head->next;
        BOX* to = belt[src].tail->prev;

        move(dst, src, from, to, cnt);
    }
    return belt[dst].count;
}
//src->dst로 count개만 옮겨라
void move(int dst, int src, int count) {
    BOX* from = belt[src].head->next;
    BOX* to = from;

    for (int i = 1; i < count; ++i) to = to->next;
    //더 정확히 from,to 잡고 move함수로 가자
    move(dst, src, from, to, count);
}
//src<->dst 서로 맨 앞 선물 교체
int q_300() {
    int src, dst;
    cin >> src >> dst;
    src--, dst--;
    //둘 다 비어있으면 그냥 바로 0 출력, dst의 선물 갯수 출력이니까
    if (empty(src) && empty(dst)) return 0;
    else if (empty(src)) move(src, dst, 1);
    else if (empty(dst)) move(dst, src, 1);
    else {
        //서로 하나씩 주고 받으려면 이렇게 하면 됨
        //src->dst로 하나 보내고
        move(dst, src, 1);
        //그럼 dst가 원래 보낼 껀 2번째로 이동해서 2개를 보낸다
        move(src, dst, 2);
        //그럼 원래 보냈던 src 첫번째가 다시 넘어왔으니까 그것만 src로 보내줌
        move(dst, src, 1);
    }

    return belt[dst].count;
}
//src->dst로 count만큼 선물 옮기기
int q_400() {
    int src, dst;
    cin >> src >> dst;
    src--, dst--;

    int count = belt[src].count / 2;
    //0보다 클 때만 처리하자
    if (count > 0) {
        move(dst, src, count);
    }
    return belt[dst].count;
}
int q_500() {
    int idx;
    cin >> idx;
    --idx;

    BOX* item = box_map[idx];
    BOX* prev = item->prev;
    BOX* next = item->next;

    //해딩 선물이 맨 앞이나 맨 뒤이면 -1해야함
    int a = (prev->prev == NULL) ? (-1) : (prev->idx + 1);
    int b = (next->next == NULL) ? (-1) : (next->idx + 1);

    return (a + (2 * b));
    
}
int q_600() {
    int belt_num;
    cin >> belt_num;
    --belt_num;

    BOX* begin = belt[belt_num].head->next;
    BOX* end = belt[belt_num].tail->prev;

    int a = (empty(belt_num)) ? -1 : begin->idx + 1;
    int b = (empty(belt_num)) ? -1 : end->idx + 1;
    int c = belt[belt_num].count;
    return (a + (2 * b) + (3 * c));
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
            break;
        case 200:
            cout << q_200() << "\n";
            break;
        case 300:
            cout << q_300() << "\n";
            break;
        case 400:
            cout << q_400() << "\n";
            break;
        case 500:
            cout << q_500() << "\n";
            break;
        case 600:
            cout << q_600() << "\n";
            break;
        }
    }
    return 0;
}