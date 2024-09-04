#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::symc_with_stdio(false);
    cin.tie(NULL);
    // 여기에 코드를 작성해주세요.
    int n;
    cin>>n;
    unordered_map<int,int> m;
    for(int i=0;i<n;++i){
        string ord;
        cin>>ord;
        if(ord=="add"){
            int a,b;
            cin>>a>>b;
            m[a]=b;
        }
        else if(ord=="remove"){
            int a;
            cin>>a;
            m.erase(a);
        }
        else if(ord=="find"){
            int a;
            cin>>a;
            if(m.find(a) == m.end()) cout<<"None\n";
            else cout<<m[a]<<"\n";
        }
    }
    return 0;
}