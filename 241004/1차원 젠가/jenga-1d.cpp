#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    vector<int> v;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        v.push_back(num);
    }
    //2번 뺌
    for (int i = 0; i < 2; ++i) {
        int s, e;
        cin >> s >> e;
        --s, --e;

        vector<int> candi;
        for (int j = 0; j < v.size(); ++j) {
            if (j >= s && j <= e) continue;
            candi.push_back(v[j]);
        }
        v = candi;
    }
    //결과
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); ++i) cout << v[i] << "\n";
    return 0;
}