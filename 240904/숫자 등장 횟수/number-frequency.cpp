#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    unordered_map<int,int> m;
    
    cin>>n;

    for(int i=0;i<n;++i){
        int num;
        cin>>num;
        m.insert({num,i+1});
    }
    int k;
    cin>>k;
    cout<<m[k];
    return 0;
}