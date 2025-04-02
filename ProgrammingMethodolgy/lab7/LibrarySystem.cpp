#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;
const int MAX_USERS = 100;

class Book {
    // TODO: Declare member variables
    // int id;
    // string title;
    // bool isBorrowed;
private:
    int id;
    string title;
    bool isBorrowed;    

public:
    void input();             // Read book info
    void borrow();            // Mark as borrowed
    void returnBook();        // Mark as returned
    bool available();   // Check availability
    int getId();
    string getTitle();
};

void Book::input(){
    cin>>id>>title;
};
void Book::borrow(){
    isBorrowed=true;
};
void Book::returnBook(){
    isBorrowed=false;
};
bool Book::available(){
    return !isBorrowed;
};
int Book::getId(){
    return id;
};
string Book::getTitle(){
    return title;
};

class User {
    // TODO: Declare member variables..
    // int id;
    // string name;
    // int borrowedBookId; // -1 if no book
private:
    int id;
    int borrowedBookId; 
    string name;
public:
    void input();                 // Read user info
    bool hasBook();        
    int getId();
    string getName();
    int getBorrowedBookId();
    void borrowBook(int bookId); 
    void returnBook();           
};

// TODO: Define Book member functions here


// TODO: Define User member functions here
void User:: input(){
    cin >> id >>name;
    borrowedBookId=-1;
};
bool User:: hasBook(){
    return borrowedBookId != -1;
};
int User:: getId(){
    return id;
};
string User:: getName(){
    return name;
};
int User:: getBorrowedBookId(){
    return borrowedBookId;
};

void User:: borrowBook(int bookId){
    borrowedBookId=bookId;
}

void User::returnBook(){
    borrowedBookId=-1;
}
// TODO: Implement helper functions to find user/book by ID
int findUserbyId(int userId, User users[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].getId() == userId)
            return i;
    }
    return -1;
}

int findBookbyId(int bookId, Book books[], int bookCount) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].getId() == bookId)
            return i;
    }
    return -1;
}


bool find(int userId, int bookId, User users[], Book books[], int userCount, int bookCount) {
    int userIdx = findUserbyId(userId, users, userCount);
    int bookIdx = findBookbyId(bookId, books, bookCount);

    if (userIdx == -1 || bookIdx == -1)
        return false;

    User& myuser = users[userIdx];
    Book& mybook = books[bookIdx];

    return !myuser.hasBook() && mybook.available();
}

int main() {
    Book books[MAX_BOOKS];
    User users[MAX_USERS];
    int bookCount = 0, userCount = 0;

    string command;
    while (cin >> command) {
        if (command == "BOOKS") {
            cin >> bookCount;
            for (int i = 0; i < bookCount; ++i) {
                books[i].input();
            }
        } else if (command == "USERS") {
            cin >> userCount;
            for (int i = 0; i < userCount; ++i) {
                users[i].input();
            }
        } else if (command == "BORROW") {
            int userId, bookId;
            cin >> userId >> bookId;
            // TODO: Find user and book
 
            int userIdx = findUserbyId(userId, users, userCount);
            int bookIdx = findBookbyId(bookId, books, bookCount);
            if (find(userId, bookId, users, books, userCount, bookCount)) {
                users[userIdx].borrowBook(books[bookIdx].getId());
                books[bookIdx].borrow();
            };


            // If user does not have a book and book is available,
            // perform borrow logic
        } else if (command == "RETURN") {
            int userId;
            cin >> userId;

            // TODO: Find user and return their book if they have one

            int userIdx = findUserbyId(userId, users, userCount);
            if (userIdx != -1 && users[userIdx].hasBook()) {
                int bookId = users[userIdx].getBorrowedBookId();
                int bookIdx = findBookbyId(bookId, books, bookCount);
                
                books[bookIdx].returnBook();
                users[userIdx].returnBook();
            };
  
        } else if (command == "END") {
            break;
        }
    }

    // TODO: Print report
    // For each user:
    // If they have a book: print "<name> has borrowed "<title>"."
    // Otherwise: print "<name> has no book."
    for (int i = 0; i < userCount; i++) {
        User& user = users[i];
        if (user.hasBook()) {
            int bookId = user.getBorrowedBookId();
            int bookIdx = findBookbyId(bookId, books, bookCount);  // ✅ 인덱스 변환
            if (bookIdx != -1) {
                Book& book = books[bookIdx];
                cout << user.getName() << " has borrowed \"" << book.getTitle() << "\"." << endl;
            } else {
                cout << user.getName() << " has an unknown book." << endl;
            }
        } else {
            cout << user.getName() << " has no book." << endl;
        }
    };

    return 0;
}