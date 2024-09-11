#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;
bool compare(pair<int,int> &a, pair<int,int> &b){
    if(a.second == b.second) return a.first>b.first;
    return a.second>b.second;
}
int main() {
    // 여기에 코드를 작성해주세요.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_map<int,int> m;
    int n,k;

    cin>>n>>k;

    for(int i=0;i<n;++i) {
        int num;
        cin>>num;
        m[num]++;
    }

    unordered_map<int,int>::iterator iter;
    vector<pair<int,int>> v;
    for(iter = m.begin();iter!=m.end();++iter){
        v.push_back({iter->first, iter->second});
    }

    sort(v.begin(),v.end(),compare);
    for(int i=0;i<k;++i) cout<<v[i].first<<" ";

    return 0;
}