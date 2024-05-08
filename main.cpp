#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
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
struct studAcadPerf
    {
        string course;
        vector <string> subjects;
        vector <float> subGrades;
    };
    
int studentNum = 0;
// store studentNum in a file
// create vector of courses with corresponding capacity limit and sections
struct studentInfo
{
    name fullName;
    dateOfBirth birthDate;
    studAcadPerf acadPerformance;
    char sex;
    string studentID, email, address, courseEnrolled;
    long long int phoneNumber;
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
            // create table
            char *sql = "CREATE TABLE IF NOT EXISTS students ("
                        "studentID TEXT PRIMARY KEY, "
                        "lastName TEXT, "
                        "firstName TEXT, "
                        "middleName TEXT, "
                        "sex TEXT, "
                        "birthMonth INTEGER, "
                        "birthDay INTEGER, "
                        "birthYear INTEGER, "
                        "phoneNumber BIGINT, "
                        "email TEXT, "
                        "address TEXT, "
                        "courseEnrolled TEXT"
                        ");";
            rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
            if (rc != SQLITE_OK)
            {
                cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }
            sqlite3_close(db);
    }
    void push2Dbase(){
        sqlite3 *db;
            int rc;
            // open dBase
            rc = sqlite3_open("Student Information.db", &db);
            if (rc != SQLITE_OK)
            {
                cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }
            if (studInfo.size() > 0)
            {
                for (int i = 0; i < studInfo.size(); i++)
                {
                    char* errMsg;
                    string sqlInsert = "INSERT INTO students (studentID, lastName, firstName, middleName, sex, birthMonth, birthDay, birthYear, phoneNumber, email, address, courseEnrolled)"
                                        "VALUES ("
                                        "'"+ studInfo[i].studentID +"',"
                                        "'"+ studInfo[i].fullName.lastName +"',"
                                        "'"+ studInfo[i].fullName.firstName +"',"
                                        "'"+ studInfo[i].fullName.middleName +"',"
                                        "'"+ studInfo[i].sex + "',"
                                        "'"+ to_string(studInfo[i].birthDate.month) + "',"
                                        "'"+ to_string(studInfo[i].birthDate.day) +"',"
                                        "'"+ to_string(studInfo[i].birthDate.year) +"',"
                                        "'"+ to_string(studInfo[i].phoneNumber) +"',"
                                        "'"+ studInfo[i].email +"',"
                                        "'"+ studInfo[i].address +"',"
                                        "'"+ studInfo[i].courseEnrolled +"'"
                                        ");";
                    rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &errMsg);
                    if (rc != SQLITE_OK)
                    {
                        cerr << "SQL Insert error: " << errMsg << endl;
                        sqlite3_free(errMsg);
                    }
                    
                }                
            }
        sqlite3_close(db);
    }
    void pullFDbase(){
        sqlite3 *db;
        int rc;
        rc = sqlite3_open("Student Information.db", &db);
        if (rc != SQLITE_OK)
        {
            cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
        }
        const char* sql = "SELECT studentID, "
                                "lastName, "
                                "firstName, "
                                "middleName, "
                                "sex, "
                                "birthMonth, "
                                "birthDay, "
                                "birthYear, "
                                "phoneNumber, "
                                "email, "
                                "address, "
                                "courseEnrolled"
                                "FROM students;";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Error SELECT statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            
        }
        
        
    }
    public:
    void runCreateDB(){
        createDB();
    }
    void runPush2DB(){
        push2Dbase();
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
                cout << "|----Student Registration & Enrollment---|\n";
                cout << "| 1. Register New Student                |\n";
                cout << "| 2. Enroll Student in Course            |\n";
                cout << "| 3. Drop Course                         |\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                    cout << "|----------Register New Student----------|\n";
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
                                        cout << "|-------------Invalid Input!-------------|\n";
                                    }
                        } while (student.sex != 'm' && student.sex != 'M' && student.sex != 'f' && student.sex != 'F');
                        // get birthdate and return if invalid
                        do
                        {
                            cout << "Enter Birthdate:" << endl << "Month (1-12): ";
                            cin >> student.birthDate.month;
                                if (student.birthDate.month > 12 || student.birthDate.month <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
                                }                                       
                        } while (student.birthDate.month > 12 || student.birthDate.month <= 0);
                        do
                        {
                            cout << "Day (1-31): ";
                            cin >> student.birthDate.day;
                                if (student.birthDate.day > 31 || student.birthDate.day <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
                                }
                        } while (student.birthDate.day > 31 || student.birthDate.day <= 0);
                        do
                        {
                            cout << "Year (~2024): ";
                            cin >> student.birthDate.year;
                                if (student.birthDate.year <= 1900 || student.birthDate.year <= 1900 || student.birthDate.day <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
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
                        student.studentID = to_string(year) + "-SC-" + to_string(studentNum);
                        student.courseEnrolled = "Not Enrolled";
                    // push data to vector
                    studInfo.push_back(student);
                    // to use studInfo[index].1ststruct.nestedstruct;
                    cout << "|-----------Student Registered-----------|\n";
                    printStudentInfo(studentNum - 1);
                    cout << "|----------------------------------------|\n";
                    break;
                case 2:
                    cout << "|--------Enroll Student in Course--------|\n";
                    cout << "|------------Available Courses-----------|\n";
                    cout << "| 1. Bachelor of Information Technology  |\n";
                    cout << "| 2. Bachelor of Business Administration |\n";
                    cout << "| 3. Bachelor of |\n";
                    cout << "|----------------------------------------|\n";
                    break;
                case 3:

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                    cout << "|-----------Invalid Selection!-----------|\n";
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
                cout << "|---------Manage Student Records---------|\n";
                cout << "| 1. View Student Details                |\n";
                cout << "| 2. Edit Student Details                |\n";
                cout << "| 3. Delete Student Record               |\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                cout << "|----------View Student Details----------|\n";
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
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
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
                                cout << "|------------Change Full Name------------|\n";
                                cout << "a. Last Name   :: ";
                                cin.ignore();
                                getline(cin, studInfo[i].fullName.lastName);
                                cout << "b. First Name  :: ";
                                getline(cin, studInfo[i].fullName.firstName);
                                cout << "c. Middle Name :: ";
                                getline(cin, studInfo[i].fullName.middleName);
                                cout << "|-----FullName modified successfully-----|\n";
                                    break;
                                case 2:
                                    cout << "|---------------Change Sex---------------|\n";
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
                                                cout << "|-------------Invalid Input!-------------|";
                                            }
                                            
                                    } while (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F');
                                    cout << "|--------Sex Successfully Changed--------|\n";
                                    break;
                                case 3:
                                cout << "|------------Change BirthDate------------|\n";
                                    do
                                    {
                                        cout << "Month (1-12)   :: ";
                                        cin >> studInfo[i].birthDate.month;
                                            if (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }                                       
                                    } while (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0);
                                    do
                                    {
                                        cout << "Day            :: ";
                                        cin >> studInfo[i].birthDate.day;
                                            if (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }
                                    } while (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0);
                                    do
                                    {
                                        cout << "Year: ";
                                        cin >> studInfo[i].birthDate.year;
                                            if (studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }
                                    } while (studInfo[i].birthDate.year > 2024 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0);                            
                                            cout << "|-----Birthdate changed Successfully-----|\n";
                                    break;
                                case 4:
                                    cout << "|-----------Change PhoneNumber-----------|\n";
                                    cout << "Phone Number: ";
                                    cin >> studInfo[i].phoneNumber;
                                    cout << "|----------------------------------------|\n";
                                    cout << "|----PhoneNumber Changed Successfully----|\n";
                                    break;
                                case 5:
                                    cout << "|----------Change Email Address----------|\n";
                                    cout << "Email Address: ";
                                    cin >> studInfo[i].email;
                                    cout << "|---Email Address Changed Successfully---|\n";
                                    break;
                                case 6:
                                    cout << "|-------------Change Address-------------|\n";
                                    cout << "Address: ";
                                    cin >> studInfo[i].address;
                                    cout << "|------Address Changed Successfully------|\n";
                                    break;
                                case 7:
                                    //need course shifting algorithm
                                    //change subjects and drop subject
                                    cout << "|---------Change Course Enrolled---------|\n";
                                    cout << "Course Enrolled: ";
                                    cin >> studInfo[i].courseEnrolled;
                                    cout << "|--Course Enrolled Changed Successfully--|\n";
                                    break;
                                case 8:
                                    continue;
                                    break;
                                default:
                                    cout << "|-----------Invalid Selection!-----------|\n";
                                    break;
                                }
                        }
                    }
                        if (!found)
                        {
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
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
                                cout << "|-----Student Information Deleted!!!-----|\n";
                            }
                            else
                            {
                                cout << "|-----StudentInformation Not Deleted-----|\n";
                            }
                        }
                    }
                        if (!found)
                        {
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                        }

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                cout << "|-----------Invalid Selection!-----------|\n";
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
                cout << "|------------Generate Reports------------|\n";
                cout << "| 1. Generate Student List               |\n";
                cout << "| 2. Generate Course Schedule            |\n";
                cout << "| 3. Generate Academic Performance Report|\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                if (studInfo.size() <= 0)
                {
                cout << "|----------------------------------------|\n";
                cout << "|---------No Students Registered---------|\n";
                cout << "|----------------------------------------|\n";
                }
                else
                {
                cout << "|--------------Student List--------------|\n";
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        cout << studInfo[i].studentID << " :: ";
                        cout << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                    }
                cout << "|----------------------------------------|\n";                    
                }
                    break;
                case 2:
                /*
                    for course schedule generation
                    Will integrate Google Gemini API if I can learn it
                    Google Gemini API is free so, will take advantage of that
                */
                    break;
                case 3:

                    break;
                case 4:
                loop = false;
                    break;
                
                default:
                cout << "|-----------Invalid Selection!-----------|\n";
                    break;
                }
            }
        }

    public:

    void runStdRegEnroll(){
        stdRegNenroll();
    }
    void runStdRecords(){
        mgmStdRecords();
    }
    void runMngGrades(){
        mngGrades();
    }
    void runGenReports(){
        genReports();
    }
};

int main()
{
    processing process;
    dBaseAccess accessDbase;
    int sel;
    char selC;    
    accessDbase.runCreateDB();
    bool loop = true;
    while (loop)
    {
        cout << "|--------Student Management System-------|\n";
        cout << "|------------------Menu------------------|\n";
        cout << "| 1. Student Registration and Enrollment |\n";
        cout << "| 2. Manage Student Records              |\n";
        cout << "| 3. Manage Student Perfomance           |\n";
        cout << "| 4. Generate Reports                    |\n";
        cout << "| 5. Exit                                |\n";
        cout << "|----------------------------------------|\n";
        cout << "Selection: ";
        cin >> sel;
        switch (sel)
            {
            case 1:
                process.runStdRegEnroll();
                break;
            case 2:
                process.runStdRecords();
                break;
            case 3:
                process.runMngGrades();
                break;
            case 4:
                process.runGenReports();
                break;
            case 5:
                loop = false;
                break;
            default:
                cout << "|-----------Invalid Selection!-----------|\n";
                break;
            }
    }
    accessDbase.runPush2DB();
    return 0;
}