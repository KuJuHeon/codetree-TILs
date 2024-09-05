#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    unordered_map<int, int> um;
    int n, k;
    cin >> n >> k;

    // 수와 해당 수의 등장 횟수를 해시맵에 저장
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        um[num]++;
    }

    int cnt = 0;
    // 각 수에 대해 두 수의 합이 k가 되는 경우의 수 계산
    for (auto it = um.begin(); it != um.end(); it++) {
        int num = it->first;
        int complement = k - num;

        // 같은 수를 두 번 선택하는 경우
        if (num == complement) {
            cnt += (it->second * (it->second - 1));
        }
        // 다른 수를 선택하는 경우
        else if (um.find(complement) != um.end()) {
            cnt += it->second * um[complement];
        }
    }

    cout << cnt / 2 << endl;

    return 0;
}