#include <iostream>
using namespace std;

// TODO function declaration
int sqr(int num)
{
  return num * num;
}

int main()
{
  int num;
  cout << "Enter a number: ";
  cin >> num;

  int result;

  // TODO function call
  result = sqr(num);
  cout << "The square of " << num << " is " << result << "." << endl;
  return 0;
}
// TODO function Definition