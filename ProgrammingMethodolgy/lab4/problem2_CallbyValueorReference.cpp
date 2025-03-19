#include <iostream>
using namespace std;

// TODO Call-by-Value
int squareByValue(int x){
  x=x * x;
  return x * x;
}

// TODO Call-by-Reference
int squareByReference(int &x){
  x=x * x;
  return x;
}

int main(){
  int x = 10;
  cout << "Before funciton call: x=" << x << endl;

  squareByValue(x);
  cout << " After call-by-value: x=" << x << endl; // x remains the same

  squareByReference(x);
  cout << " After call-by-reference: x=" << x << endl; // x is modified

  return 0;
}