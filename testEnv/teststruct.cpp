#include <iostream>
#include <vector>
using namespace std;

struct name
    {
    string lastName, firstName, middleName;
    };
struct dateOfBirth
    {
        int month, day, year;
    }; 
struct studentInfo
{
    name fullName;
    dateOfBirth birthDate;
};

int main(){
    studentInfo student;
    vector <studentInfo> studInfo;
    cout << "enter first name";
    cin >> student.fullName.firstName;
    cout << "enter first name";
    cin >> student.fullName.lastName;
    cout << "enter first name";
    cin >> student.fullName.middleName;
    cout << "enter birthdate (month):";
    cin >> student.birthDate.month;
    cout << "enter birthdate (day):";
    cin >> student.birthDate.day;
    cout << "enter birthdate (year):";
    cin >> student.birthDate.year;

    studInfo.push_back(student);
    cout << studInfo[0].fullName.firstName;
    return 0;
}