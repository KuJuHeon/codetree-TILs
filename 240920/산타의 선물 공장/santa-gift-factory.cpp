#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<unordered_map>
using namespace std;

struct BOX {
    int idx;
    int weight;
    int belt;
    BOX* prev;
    BOX* next;

    BOX() {
        idx = -1, weight = -1, belt = -1;
        prev = NULL, next = NULL;
    }
};
struct BELT {
    bool is_broken;
    BOX* head;
    BOX* tail;

    BELT() {
        is_broken = false;
        head = new BOX();
        tail = new BOX();
        head->next = tail, tail->prev = head;
        head->prev = NULL, tail->next = NULL;
    }
};

int q, cmd, n, m;
BOX box[100000];
BELT belt[10];
unordered_map<int, BOX*> box_map;
bool empty(int belt_num) {
    return (belt[belt_num].head->next == belt[belt_num].tail);
}
//어떤 벨트의 가장 뒤에 넣는 함수
void push_back(int belt_num, BOX* item) {
    box_map[item->idx] = item;
    BOX* prev = belt[belt_num].tail->prev;
    BOX* next = belt[belt_num].tail;
    item->prev = prev;
    item->next = next;

    prev->next = item;
    next->prev = item;
}
void pop_front(int belt_num) {
    if (empty(belt_num)) return;
    BOX* item = belt[belt_num].head->next;
    box_map.erase(item->idx);
    BOX* prev = belt[belt_num].head;
    BOX* next = belt[belt_num].head->next->next;

    prev->next = next;
    next->prev = prev;

    item->prev = NULL;
    item->next = NULL;
}
void q_100() {
    cin >> n >> m;
    int id[100000], w[100000];
    for (int i = 0; i < n; ++i) {
        cin >> id[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    int pos = 0;
    for (int belt_num = 0; belt_num < m; ++belt_num) {
        for (int i = 0; i < n / m; ++i) {
            box[pos].idx = id[pos];
            box[pos].weight = w[pos];
            box[pos].belt = belt_num;
            push_back(belt_num, &box[pos]);
            ++pos;
        }
    }
}
long long q_200() {
    long long ret = 0;
    int w;
    cin >> w;
    for (int i = 0; i < m; ++i) {
        //비어있거나 고장 났으면 패스
        if (empty(i) || belt[i].is_broken) continue;
        //이게 맨 앞에 있는거
        BOX* front = belt[i].head->next;
        if (front->weight <= w) {
            ret += front->weight;
            pop_front(i);
        }
        else {
            //맨 앞에꺼 빼고
            pop_front(i);
            //그 값 그대로 다시 맨 뒤로
            push_back(i, front);
        }
    }
    return ret;
}
int q_300() {
    int id;
    cin >> id;
    if (box_map.find(id) == box_map.end()) return -1;
    BOX* item = box_map[id];
    BOX* prev = item->prev;
    BOX* next = item->next;

    prev->next = next;
    next->prev = prev;

    item->prev = NULL;
    item->next = NULL;

    box_map.erase(id);
    return id;
}
int q_400() {
    int id;
    cin >> id;
    if (box_map.find(id) == box_map.end()) return -1;

    BOX* item = box_map[id];
    BOX* prev = item->prev;

    BOX* begin = belt[item->belt].head->next;
    BOX* end = belt[item->belt].tail->prev;

    if (item != begin) {
        item->prev = belt[item->belt].head;
        belt[item->belt].head->next = item;

        begin->prev = end;
        end->next = begin;

        prev->next = belt[item->belt].tail;
        belt[item->belt].tail->prev = prev;
    }
    return item->belt + 1;
}
int q_500() {
    int belt_num;
    cin >> belt_num;
    belt_num--;

    if (belt[belt_num].is_broken) return -1;
    belt[belt_num].is_broken = true;
    if (!empty(belt_num)) {
        int target = (belt_num + 1) % m;
        //false가 나올 때까지 돈다.
        while (belt[target].is_broken) {
            target = (target + 1) % m;
        }
        BOX* prev = belt[target].tail->prev;
        BOX* begin = belt[belt_num].head->next;
        BOX* end = belt[belt_num].tail->prev;

        //기존 벨트 번호에서 새로운 벨트 번호로 다 옮기자.
        for (BOX* it = begin; it != belt[belt_num].tail; it = it->next) {
            it->belt = target;
        }
        prev->next = begin;
        begin->prev = prev;
        end->next = belt[target].tail;
        belt[target].tail->prev = end;

        belt[belt_num].head->next = belt[belt_num].tail;
        belt[belt_num].tail->prev = belt[belt_num].head;
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
        }
    }

    return 0;
}