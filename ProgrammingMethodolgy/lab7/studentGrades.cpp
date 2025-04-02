#include <iostream>
using namespace std;

const int SUBJECTS = 3;
const int MAX_STUDENTS = 100;

class Student {
    // TODO: Declare member variables and functions
    private:
        int scores[3];
        float average;
    public:
        void input();
        void  calculate();
        float getAverage() const;

};

// TODO: Define member functions below
void Student::input(){

    for ( int i=0; i<3; i++){
        cin >> scores[i];
    };
};

void Student::calculate(){
        average= (scores[0]+scores[1]+scores[2])/3.0;
};

float Student::getAverage() const {

    return average;
};
// Do not modify main()
int main() {
    int n;
    Student students[MAX_STUDENTS];

    cin >> n;

    for (int i = 0; i < n; ++i) {
        students[i].input();
        students[i].calculate();
    }

    for (int i = 0; i < n; ++i) {
        printf("%.2f\n", students[i].getAverage());
    }

    return 0;
}