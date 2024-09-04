#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s[100001];
    unordered_map<string,int> s2; 
    int n,m;

    cin>>n>>m;

    for(int i=0;i<n;++i) {
        cin>>s[i+1];
        s2.insert({s[i+1],i+1});
    }
    for(int i=0;i<m;++i){
        string key;
        cin>>key;
        //숫자 형태면
        if(key[0] >= '1' && key[0] <='9'){
            cout<<s[stoi(key)]<<"\n";
        }
        else cout<<s2[key]<<"\n";
    }
    return 0;
}