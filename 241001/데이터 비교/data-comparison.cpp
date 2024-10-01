#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n1,n2;
    unordered_set<int> us;
    cin>>n1;
    while(n1--){
        int num;
        cin>>num;
        us.insert(num);
    }

    cin>>n2;
    while(n2--){
        int num;
        cin>>num;
        if(us.find(num) == us.end()) cout<< 0 <<" ";
        else cout<<1<<" ";
    }
    return 0;
}