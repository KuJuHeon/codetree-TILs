#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // 여기에 코드를 작성해주세요.
    string arr[100000];
    int n;
    cin>>n;
    for(int i=0;i<n;++i) cin>>arr[i];

    unordered_map<string, int> m;
    int MAX=0xffffffff;
    for(int i=0;i<n;++i){
        string s=arr[i];
        //문자열 없으면
        if(m.find(s) == m.end()) m[s]=1;
        else m[s]++;
        
        MAX=max(MAX,m[s]);
    }
    cout<<MAX;

    return 0;
}