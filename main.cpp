#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sqlite3.h>
using namespace std;

//get time
time_t t = time(nullptr);
tm *const pTInfo = localtime(&t);
int year = 1900 + pTInfo->tm_year;

struct name
    {
    string lastName, firstName, middleName;
    };
struct dateOfBirth
    {
        int month, day, year;
    }; 
int studentNum = 0;
struct studentInfo
{
    string studentID;
    name fullName;
    dateOfBirth birthDate;
    char sex;
    long long int phoneNumber;
    string email;
    string address;
    string courseEnrolled;
};

vector <studentInfo> studInfo;

class dBaseAccess{
    private:
    void createDB(){
        sqlite3 *db;
            int rc;
            // open database or create pag wala
            rc = sqlite3_open("Student Information.db", &db);
            // error handling
            if (rc != SQLITE_OK)
            {
                cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }


    }
    public:
    void runCreateDB(){
        createDB();
    }
};

class processing{
    private:
        void printStudentInfo(int target){
            cout << "Student ID      :: " << studInfo[target].studentID << endl;
            cout << "Full Name       :: " << studInfo[target].fullName.lastName << ", " << studInfo[target].fullName.firstName << ' ' << studInfo[target].fullName.middleName << endl;
            cout << "Sex             :: " << studInfo[target].sex << endl;
            cout << "Date of Birth   :: " << studInfo[target].birthDate.month << '/' << studInfo[target].birthDate.day << '/' << studInfo[target].birthDate.year << endl;
            cout << "Phone Number    :: " << studInfo[target].phoneNumber << endl;
            cout << "Email           :: " << studInfo[target].email << endl;
            cout << "Address         :: " << studInfo[target].address << endl;
            cout << "Course Enrolled :: " << studInfo[target].courseEnrolled << endl;
        }

        void stdRegNenroll(){
            int sel;
            bool loop = true;
            while (loop)
            {
                studentInfo student;
                cout << "1. Register New Student" << endl;
                cout << "2. Enroll Student in Course" << endl;
                cout << "3. Drop Course" << endl;
                cout << "4. Back" << endl;
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                    cout << "----Register New Student----\n";
                    // get full name
                    cout << "Enter Last Name: ";
                    cin.ignore(); //ignore the line above
                    getline(cin, student.fullName.lastName);
                    cout << "Enter First Name: ";
                    getline(cin, student.fullName.firstName);
                    cout << "Enter Middle Name: ";
                    getline(cin, student.fullName.middleName);
                        //get sex orientation and retyrn if invalid
                        do
                        {
                            cout << "Enter Sex (M/F): ";
                            cin >> student.sex; 
                                if (student.sex == 'm')
                                {
                                    student.sex = 'M';
                                }
                                else if (student.sex == 'f')
                                {
                                    student.sex = 'F';
                                }
                                    if (student.sex != 'm' && student.sex != 'M' && student.sex != 'f' && student.sex != 'F')
                                    {
                                        cout << "Invalid Input!";
                                    }
                        } while (student.sex != 'm' && student.sex != 'M' && student.sex != 'f' && student.sex != 'F');
                        // get birthdate and return if invalid
                        do
                        {
                            cout << "Enter Birthdate:" << endl << "Month (1-12): ";
                            cin >> student.birthDate.month;
                                if (student.birthDate.month > 12 || student.birthDate.month <= 0)
                                {
                                    cout << "Invalid input!\n";
                                }                                       
                        } while (student.birthDate.month > 12 || student.birthDate.month <= 0);
                        do
                        {
                            cout << "Day (1-31): ";
                            cin >> student.birthDate.day;
                                if (student.birthDate.day > 31 || student.birthDate.day <= 0)
                                {
                                    cout << "Invalid input!\n";
                                }
                        } while (student.birthDate.day > 31 || student.birthDate.day <= 0);
                        do
                        {
                            cout << "Year (~2024): ";
                            cin >> student.birthDate.year;
                                if (student.birthDate.year <= 1900 || student.birthDate.year <= 1900 || student.birthDate.day <= 0)
                                {
                                    cout << "Invalid input!\n";
                                }
                        } while (student.birthDate.year > 2024 || student.birthDate.year <= 1900 || student.birthDate.day <= 0);
                        cout << "Enter Phone Number: ";
                        cin >> student.phoneNumber;
                        cout << "Enter Email Address: ";
                        cin >> student.email;
                        cin.ignore(); // ignore above nanaman
                        cout << "Enter Address: ";
                        getline(cin, student.address);
                        studentNum++;
                        student.studentID = to_string(year) + "--SC--" + to_string(studentNum);
                        student.courseEnrolled = "Not Enrolled";
                    // push data to vector
                    studInfo.push_back(student);
                    // to use studInfo[index].1ststruct.nestedstruct;
                    cout << "-----Student Registered-----\n";
                    printStudentInfo(studentNum - 1);
                    cout << "----------------------------\n";
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                    cout << "Invalid Selection!!!\n";
                    break;
                }
            }
        }

        void mgmStdRecords(){
            int sel;
            bool loop = true;
            while (loop)
            {
                string findID;
                bool found = false;
                cout << "1. View Student Details" << endl;
                cout << "2. Edit Student Details" << endl;
                cout << "3. Delete Student Record" << endl;
                cout << "4. Back" << endl;
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                cout << "Enter Student Id: ";
                cin >> findID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            printStudentInfo(i);
                            found = true;
                        }
                    }
                        if (!found)
                        {
                            cout << "Student Not Found!\n";
                        }
                    break;
                case 2:
                int selection;
                cout << "Enter Student ID to edit: ";
                cin >> findID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            cout << "~~ Student ID      :: " << studInfo[i].studentID << endl;
                            cout << "1. Full Name       :: " << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                            cout << "2. Sex             :: " << studInfo[i].sex << endl;
                            cout << "3. Date of Birth   :: " << studInfo[i].birthDate.month << '/' << studInfo[i].birthDate.day << '/' << studInfo[i].birthDate.year << endl;
                            cout << "4. Phone Number    :: " << studInfo[i].phoneNumber << endl;
                            cout << "5. Email           :: " << studInfo[i].email << endl;
                            cout << "6. Address         :: " << studInfo[i].address << endl;
                            cout << "7. Course Enrolled :: " << studInfo[i].courseEnrolled << endl;
                            cout << "8. Cancel" << endl;
                            found = true;
                            cout << "Selection: ";
                            cin >> selection;
                                switch (selection)
                                {
                                case 1:
                                cout << "-----------Change Full Name-----------\n";
                                cout << "a. Last Name   :: ";
                                cin.ignore();
                                getline(cin, studInfo[i].fullName.lastName);
                                cout << "b. First Name  :: ";
                                getline(cin, studInfo[i].fullName.firstName);
                                cout << "c. Middle Name :: ";
                                getline(cin, studInfo[i].fullName.middleName);
                                cout << "---Full Name modified successfully---\n";
                                    break;
                                case 2:
                                    cout << "-----Change Sex-----\n";
                                    do
                                    {
                                        cout << "Enter Sex (M/F): ";
                                        cin >> studInfo[i].sex;
                                        if (studInfo[i].sex == 'm')
                                        {
                                            studInfo[i].sex = 'M';
                                        }
                                        else if (studInfo[i].sex == 'f')
                                        {
                                            studInfo[i].sex = 'F';
                                        }
                                            if (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F')
                                            {
                                                cout << "Invalid Input!";
                                            }
                                            
                                    } while (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F');
                                    cout << "-----Sex Successfully Changed-----\n";
                                    break;
                                case 3:
                                cout << "-------------Change Birth Date--------\n";
                                    do
                                    {
                                        cout << "Month (1-12)   :: ";
                                        cin >> studInfo[i].birthDate.month;
                                            if (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0)
                                            {
                                                cout << "Invalid input!";
                                            }                                       
                                    } while (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0);
                                    do
                                    {
                                        cout << "Day            :: ";
                                        cin >> studInfo[i].birthDate.day;
                                            if (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "Invalid input!";
                                            }
                                    } while (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0);
                                    do
                                    {
                                        cout << "Year: ";
                                        cin >> studInfo[i].birthDate.year;
                                            if (studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "Invalid input!";
                                            }
                                    } while (studInfo[i].birthDate.year > 2024 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0);                            
                                            cout << "--------Birthdate changed Successfully---------";
                                    break;
                                case 4:
                                    cout << "-----Change Phone Number-----\n";
                                    cout << "Phone Number: ";
                                    cin >> studInfo[i].phoneNumber;
                                    cout << "-----Phone Number Changed Successfully-----";
                                    break;
                                case 5:
                                    cout << "-----Change Email Address-----\n";
                                    cout << "Email Address: ";
                                    cin >> studInfo[i].email;
                                    cout << "-----Email Address Changed Successfully-----";
                                    break;
                                case 6:
                                    cout << "-----Change Address-----\n";
                                    cout << "Address: ";
                                    cin >> studInfo[i].address;
                                    cout << "-----Address Changed Successfully-----";
                                    break;
                                case 7:
                                    cout << "-----Change Course Enrolled-----\n";
                                    cout << "Course Enrolled: ";
                                    cin >> studInfo[i].courseEnrolled;
                                    cout << "-----Course Enrolled Changed Successfully-----";
                                    break;
                                case 8:
                                    continue;
                                    break;
                                default:
                                cout << "Invalid Selection!!";
                                    break;
                                }
                        }
                    }
                        if (!found)
                        {
                            cout << "Student not found!!!\n";
                        }
                    break;
                case 3:
                char delet3;
                cout << "Enter Student ID: ";
                cin >> findID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            printStudentInfo(i);
                            found = true;
                            cout << "Do you really want to delete this student record (Y/N)?: ";
                            cin >> delet3;
                            if (delet3 == 'Y' || delet3 == 'y')
                            {
                                studInfo.erase(studInfo.begin() + i);
                                cout << "Student Information Deleted!!!!";
                            }
                            else
                            {
                                cout << "Student Information Not Deleted";
                            }
                        }
                    }
                        if (!found)
                        {
                            cout << "Student Not Found!\n";
                        }

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                    cout << "Invalid Selection!!!";
                    break;
                }
            }
        }

        void mngGrades(){

        }

        void genReports(){
            int sel;
            bool loop = true;
            while(loop)
            {
                cout << "1. Generate Student List" << endl;
                cout << "2. Generate Course Schedule" << endl;
                cout << "3. Generate Academic Performance Report" << endl;
                cout << "4. Back" << endl;
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                    /* code */
                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                    cout << "Invalid Selection!!!";
                    break;
                }
            }
        }

    public:
        void getMainUserSelect(int sel){
            switch (sel)
            {
            case 1:
                stdRegNenroll();
                break;
            case 2:
                mgmStdRecords();
                break;
            case 3:
                mngGrades();
                break;
            case 4:
                genReports();
                break;
            default:
                cout << "Invalid Input\n";
                break;
            }
        }
};



int main(){
    processing process;
    dBaseAccess databaseAccess;
    databaseAccess.runCreateDB();
    int sel;
    char selC;
    while ("true")
    {
        cout << "Student Management System\n";
        cout << "-----------Menu-----------\n";
        cout << " 1. Student Registration and Enrollment\n";
        cout << " 2. Manage Student Records\n";
        cout << " 3. Manage Student Perfomance\n";
        cout << " 4. Generate Reports\n";
        cout << "Selection: ";
        cin >> sel;
        process.getMainUserSelect(sel);
    }
    return 0;
}