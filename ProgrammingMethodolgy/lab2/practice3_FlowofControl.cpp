#include <iostream>
using namespace std;

int main(){
    int input,i,j;
    cout<<"input number>>";
    cin>>input;

    for(i=0;i<input;i=i+2){
        for(j=0;j<i;j=j+2){
            cout<<"**";
        }
        cout<<""<<endl;
        cout<<""<<endl;
    }
}
//print "*" n times but skip oddlines