#include <ctime>
#include <iostream>
using namespace std;

int main() {
    time_t t = time(nullptr);
    tm *const pTInfo = localtime(&t);
    string studentID;
    int year = 1900 + pTInfo->tm_year;
    studentID = to_string(year) + "-SC-" + "1";
    cout << "HEHHEHE: " << studentID;
}
