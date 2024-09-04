#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    // 여기에 코드를 작성해주세요.
    int n,m;
    unordered_map<int,int> num;
    
    cin>>n>>m;

    for(int i=0;i<n;++i){
        int a;
        cin>>a;
        num[a]++;
    }
    for(int i=0;i<m;++i){
        int k;
        cin>>k;
        cout<<num[k] <<" ";
    }
    
    return 0;
}