#include <iostream>
#include <iomanip>
#include <cstdlib>

using std::cout;
using std::endl;

int main(){
  int price[1000];
  for (int i=0;i<1000;i++){
    price[i]=i;
  }
  int sum=0;
  for(int i=0;i<1000;i++){
    sum+=price[999-i];
    
  }
  cout << sum<<endl;

  return 0;
}
