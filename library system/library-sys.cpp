#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

time_t t = time(nullptr);
tm *const pTInfo = localtime(&t);
int day = pTInfo->tm_mday;
int month = pTInfo->tm_mon + 1;
int year = pTInfo->tm_year + 1900;

struct date {
    int day;
    int month;
    int year;
};

struct Book {
    string name;
    string id;
    string author;
    string publisher;
    string borrowedby;
    date dateBorrowed;
    bool available;
};

struct User {
    string username;
    string password;
};

vector <Book> books;
vector <User> users;

void pushUsersToTxt() {
    ofstream file("users.txt");
    if (file.is_open()) 
    {
        for (int i = 0; i < users.size(); i++) {
            file << "Username: " << users[i].username << endl;
            file << "Password: " << users[i].password << endl;
        }
        file.close();
    } 
    else 
    {
        cout << "|==================================================|" << endl;
        cout << "|============== Unable to open file! ==============|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void pullUsersFromTxt() {
    ifstream file("users.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            User user;
            user.username = line.substr(line.find(":") + 2);
            getline(file, line);
            user.password = line.substr(line.find(":") + 2);
            users.push_back(user);
        }
        file.close();
    } else {
        ofstream createFile("users.txt");
        createFile.close();
    }
}

void pushBooksToTxt() {
    ofstream file("books.txt");
    if (file.is_open()) {
        for (int i = 0; i < books.size(); i++) {
            file << "Book Name: " << books[i].name << endl;
            file << "Book ID: " << books[i].id << endl;
            file << "Author: " << books[i].author << endl;
            file << "Publisher: " << books[i].publisher << endl;
            file << "Available: " << (books[i].available ? "Yes" : "No") << endl;
            file << "Borrowed By: " << books[i].borrowedby << endl;
            file << "Day Borrowed: " << books[i].dateBorrowed.day << endl;
            file << "Month Borrowed: " << books[i].dateBorrowed.month << endl;
            file << "Year Borrowed: " << books[i].dateBorrowed.year << endl;
            file << endl;
        }
        file.close();
    } else {
        cout << "|==================================================|" << endl;
        cout << "|============== Unable to open file! ==============|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void pullBooksFromTxt()
{
    ifstream file("books.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) 
        {
            if (!line.empty()) {
                Book book;
                book.name = line.substr(line.find(":") + 2);
                getline(file, line);
                book.id = line.substr(line.find(":") + 2);
                getline(file, line);
                book.author = line.substr(line.find(":") + 2);
                getline(file, line);
                book.publisher = line.substr(line.find(":") + 2);
                getline(file, line);
                if (!line.empty()) 
                {
                    book.available = (line.substr(line.find(":") + 2) == "Yes");
                }
                book.borrowedby = line.substr(line.find(":") + 2);
                getline(file, line);
                getline(file, line);
                book.dateBorrowed.day = stoi(line.substr(line.find(":") + 2));
                getline(file, line);
                book.dateBorrowed.month = stoi(line.substr(line.find(":") + 2));
                getline(file, line);
                book.dateBorrowed.year = stoi(line.substr(line.find(":") + 2));
                getline(file, line);
                books.push_back(book);
            }
        }
        file.close();
    } 
    else 
    {
        ofstream createFile("books.txt");
        createFile.close();
    }
    file.close();
}

bool adminLogon(string username, string password){
    string adminUsername = "admin";
    string adminPassword = "admin";
    if(username == adminUsername && password == adminPassword){
        cout << "|==================================================|" << endl;
        cout << "|================ Login successful ================|" << endl;
        cout << "|==================================================|" << endl;
        return true;
    }
        cout << "|==================================================|" << endl;
        cout << "|========== Invalid username or password ==========|" << endl;
        cout << "|==================================================|" << endl;
        return false;
}

void registerUser() {
    User user;
    bool reg = true;
    while (reg)
    {
        if (users.empty()) {
            reg = false;
        }
        cout << endl;
        cout << "|==================================================|" << endl;
        cout << "|=============== User Registration ================|" << endl;
        cout << "|==================================================|" << endl;
        cout << "Enter Username: ";
        cin >> user.username;
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].username == user.username)
            {
                cout << "|==================================================|" << endl;
                cout << "|============= Username not available =============|" << endl;
                cout << "|==================================================|" << endl;
            }
            else if (users[i].username != user.username)
            {
                reg = false;
            }
        }
    }
    cout << "| Enter Password: ";
    cin >> user.password;
    users.push_back(user);
    cout << "|==================================================|" << endl;
    cout << "|========== User registered successfully ==========|" << endl;
    cout << "|==================================================|" << endl;
    cout << endl;
}

bool loginUser(string username, string password) {
    bool found = false;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].username == username && users[i].password == password) 
        {
            found = true;
            break;
        }
    }
    if (found) 
    {
        cout << endl;
        cout << "|==================================================|" << endl;
        cout << "|================ Login successful ================|" << endl;
        cout << "|==================================================|" << endl;
        cout << endl;
        return true;
    } 
    else 
    {
        cout << endl;
        cout << "|==================================================|" << endl;
        cout << "|========== Invalid username or password ==========|" << endl;
        cout << "|==================================================|" << endl;
        cout << endl;
        return false;
    }
}

void borrowBook(string borrower) {
    string bookId;
    cout << "|================ Borrow a Book ===================|" << endl;
    cout << "| Enter Book ID: ";
    cin >> bookId;
    bool found = false;
    for (int i = 0; i < books.size(); i++){
        if (books[i].id == bookId && books[i].available) {
            found = true;
            books[i].available = false;
            books[i].borrowedby = borrower;
            books[i].dateBorrowed.day = day;
            books[i].dateBorrowed.month = month;
            books[i].dateBorrowed.year = year;
            cout << "|==================================================|" << endl;
            cout << "|=========== Book borrowed successfully ===========|" << endl;
            cout << "|==================================================|" << endl;
            break;
        }
    }
    if (!found) {
        cout << "|==================================================|" << endl;
        cout << "|======== Book not found or not available! ========|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void printOverdueBooks(){
    cout << "|================== Overdue Books =================|" << endl;
    for (int i = 0; i < books.size(); i++){
        if (!books[i].available && 
            (day - books[i].dateBorrowed.day) > 7 || 
            month != books[i].dateBorrowed.month ||
            year != books[i].dateBorrowed.year)
        {
            cout << "| Book Name: " << books[i].name << endl;
            cout << "| Book ID: " << books[i].id << endl;
            cout << "| Author: " << books[i].author << endl;
            cout << "| Publisher: " << books[i].publisher << endl;
            cout << "| Borrowed By: " << books[i].borrowedby << endl;
            cout << "| Date Borrowed: " << books[i].dateBorrowed.day << "/" << books[i].dateBorrowed.month << "/" << books[i].dateBorrowed.year << endl;
            cout << "|==================================================|" << endl;
            cout << endl;
        }
    }
}

void returnBook() {
    string bookId;
    cout << "|================ Return a Book ===================|" << endl;
    cout << "| Enter Book ID: ";
    cin >> bookId;
    bool found = false;
    for (auto& book : books) {
        if (book.id == bookId && !book.available) {
            found = true;
            book.available = true;
            book.borrowedby = "";
            cout << "|==================================================|" << endl;
            cout << "|=========== Book returned successfully ===========|" << endl;
            cout << "|==================================================|" << endl;
            break;
        }
    }
    if (!found) {
        cout << "|==================================================|" << endl;
        cout << "|======= Book not found or already returned =======|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void searchBook() {
    string bookName;
    cout << "|================ Search a Book ===================|" << endl;
    cout << "| Enter Book Name: ";
    cin.ignore();
    getline(cin, bookName);
    bool found = false;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].name == bookName) {
            found = true;
            cout << "|=================== Book found ===================|" << endl;
            cout << "| Book ID: " << books[i].id << endl;
            cout << "| Author: " << books[i].author << endl;
            cout << "| Publisher: " << books[i].publisher << endl;
            cout << "| Available: " << (books[i].available ? "Yes" : "No") << endl;
            cout << "|==================================================|" << endl;
            break;
        }
    }
    if (!found) {
        cout << "|==================================================|" << endl;
        cout << "|================= Book not found =================|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void viewAllBooks() {
        cout << "|================ All Books =======================|" << endl;
    for (const auto& book : books) {
        cout << "| Book Name: " << book.name << endl;
        cout << "| Book ID: " << book.id << endl;
        cout << "| Author: " << book.author << endl;
        cout << "| Publisher: " << book.publisher << endl;
        cout << "| Available: " << (book.available ? "Yes" : "No") << endl;
        cout << "|==================================================|" << endl;
        cout << endl;
    }
}

void viewAllAvailableBooks() {
            cout << endl;
            cout << "|============== Available Books ===================|" << endl;
    for (const auto& book : books) {
        if (book.available) {
            cout << "| Book Name: " << book.name << endl;
            cout << "| Book ID: " << book.id << endl;
            cout << "| Author: " << book.author << endl;
            cout << "| Publisher: " << book.publisher << endl;
            cout << "| Available: " << (book.available ? "Yes" : "No") << endl;
            cout << "|==================================================|" << endl;
            cout << endl;
        }
    }
}

void addBook() {
    Book book;
    cout << "|================ Add a Book =====================|" << endl;
    cout << "| Enter Book Name: ";
    cin.ignore();
    getline(cin, book.name);
    cout << "| Enter Book ID: ";
    cin >> book.id;
    cout << "| Enter Author Name: ";
    cin.ignore();
    getline(cin, book.author);
    cout << "| Enter Publisher Name: ";
    cin.ignore();
    getline(cin, book.publisher);
    book.available = true;
    books.push_back(book);
    cout << "|============ Book added successfully! ============|" << endl;
}

void removeBook() {
    string bookId;
    cout << "|================ Remove a Book ==================|" << endl;
    cout << "| Enter Book ID: ";
    cin >> bookId;
    bool found = false;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == bookId) {
            found = true;
            books.erase(books.begin() + i);
            cout << "|============ Book removed successfully ==========|" << endl;
            break;
        }
    }
    if (!found) {
        cout << "|==================================================|" << endl;
        cout << "|================= Book not found =================|" << endl;
        cout << "|==================================================|" << endl;
    }
}

void viewAllBorrowedBooks() {
    bool found = false;
    cout << "|============== Borrowed Books ===================|" << endl;
    for (int i = 0; i < books.size(); i++) {
        if (!books[i].available) {
            found = true;
            cout << "|==================================================|" << endl;
            cout << "| Book Name: " << books[i].name << endl;
            cout << "| Book ID: " << books[i].id << endl;
            cout << "| Author: " << books[i].author << endl;
            cout << "| Publisher: " << books[i].publisher << endl;
            cout << "| Borrowed By: " << books[i].borrowedby << endl;
            cout << "| Date Borrowed: " << books[i].dateBorrowed.day << "/" << books[i].dateBorrowed.month << "/" << books[i].dateBorrowed.year << endl;
            cout << "|==================================================|" << endl;
            cout << endl;
        }
    }
    if (!found) {
        cout << "|=============== No books borrowed! ===============|" << endl;
    }
}

int main() {
    pullUsersFromTxt();
    pullBooksFromTxt();
    int choice;
    bool loop = true;
    cout << "|==================================================|" << endl;
    cout << "|=========== Welcome to Library System! ===========|" << endl;
    cout << "|==================================================|" << endl;
    while (loop) 
    {
        cout << "|====================== Menu ======================|" << endl;
        cout << "| 1. User Registration                             |" << endl;
        cout << "| 2. User Login                                    |" << endl;
        cout << "| 3. Admin Login                                   |" << endl;
        cout << "| 4. Exit                                          |" << endl;
        cout << "|==================================================|" << endl;
        cout << "| Enter your choice: ";
        cin >> choice;
        if (choice == 1) 
        {
            registerUser();
        }
            else if (choice == 2) 
            {
                bool loginLoop = true;
                while (loginLoop)
                {
                    string username, password;
                    cout << "| Enter Username: ";
                    cin >> username;
                    cout << "| Enter Password: ";
                    cin >> password;
                    if (loginUser(username, password)) 
                    {
                        bool userLoop = true;
                        while (userLoop) {
                            cout << "|==================== UserMenu ====================|" << endl;
                            cout << "| 1. Borrow Book                                   |" << endl;
                            cout << "| 2. Return Book                                   |" << endl;
                            cout << "| 3. Search Book                                   |" << endl;
                            cout << "| 4. View All Books                                |" << endl;
                            cout << "| 5. View All Available Books                      |" << endl;
                            cout << "| 6. Back                                          |" << endl;
                            cout << "|==================================================|" << endl;
                            cout << "| Enter your choice: ";
                            cin >> choice;
                            switch (choice) {
                                case 1:
                                    borrowBook(username);
                                    break;
                                case 2:
                                    returnBook();
                                    break;
                                case 3:
                                    searchBook();
                                    break;
                                case 4:
                                    viewAllBooks();
                                    break;
                                case 5:
                                    viewAllAvailableBooks();
                                    break;
                                case 6:
                                    userLoop = false;
                                    loginLoop = false;
                                    break;
                                default:
                                    cout << "|==================================================|" << endl;
                                    cout << "|================= Invalid choice =================|" << endl;
                                    cout << "|==================================================|" << endl;
                                    break;
                            }
                        }
                    }
                    else
                    {
                        cout << "|==================================================|" << endl;
                        cout << "|===========Invalid username or password===========|" << endl;
                        cout << "|==================================================|" << endl;
                    }
                }
            } 
            else if (choice == 3)
            {
                string username, password;
                cout << "|==================================================|" << endl;
                cout << "|=================== AdminLogin ===================|" << endl;
                cout << "| Enter Username: ";
                cin >> username;
                cout << "| Enter Password: ";
                cin >> password;
                if (adminLogon(username, password)) 
                {
                    bool adminLoop = true;
                    while (adminLoop) 
                    {
                        cout << "Admin Menu:" << endl;
                        cout << "1. Add Book" << endl;
                        cout << "2. Remove Book" << endl;
                        cout << "3. View All Books" << endl;
                        cout << "4. View All Available Books" << endl;
                        cout << "5. View All Borrowed Books" << endl;
                        cout << "6. Print Overdue Books" << endl;
                        cout << "7. Back" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        switch (choice) 
                        {
                            case 1:
                                addBook();
                                break;
                            case 2:
                                removeBook();
                                break;
                            case 3:
                                viewAllBooks();
                                break;
                            case 4:
                                viewAllAvailableBooks();
                                break;
                            case 5:
                                viewAllBorrowedBooks();
                                break;
                            case 6:
                                printOverdueBooks();
                                break;
                            case 7:
                                adminLoop = false;
                                break;
                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                        }
                    }
                } 
                else 
                {
                    cout << "Invalid username or password!" << endl;
                    continue;
                }
            }
            else if (choice == 4) 
            {
                loop = false;
            } 
            else 
            {
                cout << "Invalid choice!" << endl;
            }
    }
    pushBooksToTxt();
    pushUsersToTxt();
    return 0;
}