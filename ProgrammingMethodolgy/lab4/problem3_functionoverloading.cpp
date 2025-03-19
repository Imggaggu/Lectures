#include <iostream>
using namespace std;

//TODO Function Overloading: add() for integers
int add(int a, int b){
  return a+b;
}
//TODO Function Overloading: add() for floating-point numbers
double add(double a, double b){
  return a+b;
}
//main
int main(){
  int x=3,y=4;
  double p=2.3, q=3.2;

  cout << "Sum of integers: "<< add(x,y)<<endl;
  cout << "Sum of floats: "<< add(p,q) <<endl;
}