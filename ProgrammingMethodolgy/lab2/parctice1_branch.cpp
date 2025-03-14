#include <iostream>
using namespace std;

int main(){
    int input;
    cout<<"input number (1-3)>>";
    cin>> input;

    switch(input){
        case 1:
            cout<<"input is 1"<<endl;
            break;
        case 2:
            cout<<"input is 2"<<endl;
            break;
        case 3:
            cout<<"input is 3"<<endl;
            break;
        default:
            cout << "invalid input"<<endl;

    }
}

//change if to switch
/*
if (input==1)
    cout <<"input is 1"<<endl;
else if(input==2)
    cout << "input is 2"<<endl
else:
    cout <<"invalid input"<<endl
*/