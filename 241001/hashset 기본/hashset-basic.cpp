#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // 여기에 코드를 작성해주세요.
    int n;
    unordered_set<int> us;

    cin>>n;
    while(n--){
        string s;
        int num;
        cin>>s>>num;
        if(s=="find"){
            if(us.find(num) == us.end()) cout<<"false\n";
            else cout<<"true\n";
        }
        else if(s=="add"){
            us.insert(num);
        }
        else if(s=="remove"){
            us.erase(num);
        }
    }
    return 0;
}