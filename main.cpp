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
struct studAcadPerf
    {
        string studId, course;
        vector <float> grades;
    };
struct name
    {
    string lastName, firstName, middleName;
    };
struct dateOfBirth
    {
        int month, day, year;
    }; 
    
int studentNum = 0;
int studentEnrolled = 0;
// store studentNum in a file
// create vector of courses with corresponding capacity limit and sections
struct studentInfo
{
    name fullName;
    dateOfBirth birthDate;
    char sex;
    string studentID, email, address, courseEnrolled;
    long long int phoneNumber;
};

vector <studentInfo> studInfo;
vector <studAcadPerf> studGrades;
int studCap[3] = {30, 30, 30};
class login
{
    private: 
        string username = "username";
        string password =  "admin";
    public:
        string getUsername(){
            return username;
        }
        string getPassword(){
            return password;
        }
};
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
            /* char *createBSBA = "CREATE TABLE IF NOT EXISTS BSBA ("
                                "studentID TEXT PRIMARY KEY, "
                                ""
                                ");"; */
            sqlite3_close(db);
    }
    void createGradingSheets(){
        sqlite3 *db;
            int rc;
            rc = sqlite3_open("Student Information.db", &db);
            if (rc != SQLITE_OK)
            {
                cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }
            char *createBSIT = "CREATE TABLE IF NOT EXISTS BSIT ("
                        "studentID TEXT PRIMARY KEY, "
                        "CC101 FLOAT, "
                        "CC102 FLOAT, "
                        "GE6 FLOAT "
                        ");";
            rc = sqlite3_exec(db, createBSIT, NULL, NULL, NULL);
            if (rc != SQLITE_OK)
            {
                cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }

            char *createBSBA = "CREATE TABLE IF NOT EXISTS BSBA ("
                                "studentID TEXT PRIMARY KEY, "
                                "testSub1 FLOAT, "
                                "testSub2 FLOAT, "
                                "testSub3 FLOAT "
                                ");";
            rc = sqlite3_exec(db, createBSBA, NULL, NULL, NULL);
            if (rc != SQLITE_OK)
            {
                cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
                sqlite3_close(db);
            }

            char *createBSA = "CREATE TABLE IF NOT EXISTS BSA ("
                                "studentID TEXT PRIMARY KEY, "
                                "testSub1 FLOAT, "
                                "testSub2 FLOAT, "
                                "testSub3 FLOAT "
                                ");";
            rc = sqlite3_exec(db, createBSA, NULL, NULL, NULL);
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
                for (int i = 0; i < studentNum; i++)
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
                            "courseEnrolled "
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
            studentInfo student;
            student.studentID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            student.fullName.lastName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            student.fullName.firstName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            student.fullName.middleName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            student.sex = *reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            student.birthDate.month = sqlite3_column_int(stmt, 5);
            student.birthDate.day = sqlite3_column_int(stmt, 6);
            student.birthDate.year = sqlite3_column_int(stmt, 7);
            student.phoneNumber = sqlite3_column_int64(stmt, 8);
            student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
            student.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
            student.courseEnrolled = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
            studInfo.push_back(student);
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    int getStudentCount(string what){
        sqlite3 *db;
        int rc;
        int returnNumber;
        rc = sqlite3_open("Student Information.db", &db);
        if (rc != SQLITE_OK)
        {
            cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
        }
            if (what == "studentNumbers")
            {
                char *getRows = "SELECT COUNT(*) FROM students;";
                sqlite3_stmt *getRowss;

                if (sqlite3_prepare_v2(db, getRows, -1, &getRowss, NULL) != SQLITE_OK)
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                }

                if (sqlite3_step(getRowss) == SQLITE_ROW)
                {
                    returnNumber = sqlite3_column_int(getRowss, 0);
                }
                else
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(getRowss);
            }
            else if (what == "BSITenrolled")
            {
                char *getBSIT = "SELECT COUNT(*) FROM BSIT;";
                sqlite3_stmt *getBSITrows;

                if (sqlite3_prepare_v2(db, getBSIT, -1, &getBSITrows, NULL) != SQLITE_OK)
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                }

                if (sqlite3_step(getBSITrows) == SQLITE_ROW)
                {
                    returnNumber = sqlite3_column_int(getBSITrows, 0);
                }
                else
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(getBSITrows);
            }
            else if (what == "BSBAenrolled")
            {
                char *getBSBA = "SELECT COUNT(*) FROM BSBA;";
                sqlite3_stmt *getBSBArows;

                if (sqlite3_prepare_v2(db, getBSBA, -1, &getBSBArows, NULL) != SQLITE_OK)
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                }

                if (sqlite3_step(getBSBArows) == SQLITE_ROW)
                {
                    returnNumber = sqlite3_column_int(getBSBArows, 0);
                }
                else
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(getBSBArows);
            }
            else if (what == "BSAenrolled")
            {
                char *getBSA = "SELECT COUNT(*) FROM BSA;";
                sqlite3_stmt *getBSArows;

                if (sqlite3_prepare_v2(db, getBSA, -1, &getBSArows, NULL) != SQLITE_OK)
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                }

                if (sqlite3_step(getBSArows) == SQLITE_ROW)
                {
                    returnNumber = sqlite3_column_int(getBSArows, 0);
                }
                else
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(getBSArows);
                
            }
            else if (what == "totalEnrolled")
            {
                char *enrolledRows = "SELECT ((SELECT COUNT(*) FROM BSA) + (SELECT COUNT(*) FROM BSIT) + (SELECT COUNT(*) FROM BSBA)) AS Total_Count;";
                sqlite3_stmt *getTotalEnrolled;
                
                if (sqlite3_prepare_v2(db, enrolledRows, -1, &getTotalEnrolled, NULL) != SQLITE_OK)
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                }

                if (sqlite3_step(getTotalEnrolled) == SQLITE_ROW)
                {
                    returnNumber = sqlite3_column_int(getTotalEnrolled, 0);
                }
                else
                {
                    cerr << "Error getting rows: " << sqlite3_errmsg(db) << endl;
                }
                sqlite3_finalize(getTotalEnrolled);
            }
            sqlite3_close(db);
            return returnNumber;
    }
    void pushGrades(){
        sqlite3 *db;
        int rc;
        char*errMsg;
        rc = sqlite3_open("Student Information.db", &db);
        if (rc != SQLITE_OK)
        {
            cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
        }
        for (int i = 0; i < studGrades.size(); i++)
        {
            if (studGrades[i].course == "Bachelor of Science in Information Technology")
            {
                string insertBSIT = "INSERT INTO BSIT (studentID, CC101, CC102, GE6)"
                                    "VALUES ("
                                    "'"+ studInfo[i].studentID +"',"
                                    "'"+ to_string(studGrades[i].grades[0]) +"',"
                                    "'"+ to_string(studGrades[i].grades[1]) +"',"
                                    "'"+ to_string(studGrades[i].grades[2]) +"'"
                                    ");";
                    rc = sqlite3_exec(db, insertBSIT.c_str(), NULL, NULL, &errMsg);
                    if (rc != SQLITE_OK)
                    {
                        cerr << "SQL Insert error: " << errMsg << endl;
                        sqlite3_free(errMsg);
                    }
            }
            else if (studGrades[i].course == "Bachelor of Science in Business Administration")
            {
                string insertBSBA = "INSERT INTO BSBA (studentID, testSub1, testSub2, testSub3)"
                                    "VALUES ("
                                    "'"+ studInfo[i].studentID +"',"
                                    "'"+ to_string(studGrades[i].grades[0]) +"',"
                                    "'"+ to_string(studGrades[i].grades[1]) +"',"
                                    "'"+ to_string(studGrades[i].grades[2]) +"'"
                                    ");";
                    rc = sqlite3_exec(db, insertBSBA.c_str(), NULL, NULL, &errMsg);
                    if (rc != SQLITE_OK)
                    {
                        cerr << "SQL Insert error: " << errMsg << endl;
                        sqlite3_free(errMsg);
                    }
            }
            else if (studGrades[i].course == "Bachelor of Science in Agriculture")
            {
                string insertBSA = "INSERT INTO BSA (studentID, testSub1, testSub2, testSub3)"
                                    "VALUES ("
                                    "'"+ studInfo[i].studentID +"',"
                                    "'"+ to_string(studGrades[i].grades[0]) +"',"
                                    "'"+ to_string(studGrades[i].grades[1]) +"',"
                                    "'"+ to_string(studGrades[i].grades[2]) +"'"
                                    ");";
                    rc = sqlite3_exec(db, insertBSA.c_str(), NULL, NULL, &errMsg);
                    if (rc != SQLITE_OK)
                    {
                        cerr << "SQL Insert error: " << errMsg << endl;
                        sqlite3_free(errMsg);
                    }
            }
        }
        sqlite3_close(db);
    }
    void pullGrades(){
        sqlite3 *db;
        int rc;
        char*errMsg;
        rc = sqlite3_open("Student Information.db", &db);
        if (rc != SQLITE_OK)
        {
            cerr << "Error Opening Database: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
        }
        const char* selectBSIT = "SELECT studentID, "
                    "CC101, "
                    "CC102, "
                    "GE6 "
                    "FROM BSIT;";
        sqlite3_stmt *selBSIT;
        rc = sqlite3_prepare_v2(db, selectBSIT, -1, &selBSIT, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Error SELECT statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(selBSIT);
            sqlite3_close(db);
        }
        while (sqlite3_step(selBSIT) == SQLITE_ROW)
        {
            studAcadPerf studentt;
            studentt.studId = reinterpret_cast<const char*>(sqlite3_column_text(selBSIT, 0));
            studentt.course = "Bachelor of Science in Information Technology";
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSIT, 1)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSIT, 2)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSIT, 3)));
            studGrades.push_back(studentt);
        }
        sqlite3_finalize(selBSIT);

        const char* selectBSBA = "SELECT studentID, "
                    "testSub1, "
                    "testSub2, "
                    "testSub3 "
                    "FROM BSBA;";
        sqlite3_stmt *selBSBA;
        rc = sqlite3_prepare_v2(db, selectBSBA, -1, &selBSBA, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Error SELECT statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(selBSBA);
            sqlite3_close(db);
        }
        while (sqlite3_step(selBSBA) == SQLITE_ROW)
        {
            studAcadPerf studentt;
            studentt.studId = reinterpret_cast<const char*>(sqlite3_column_text(selBSBA, 0));
            studentt.course = "Bachelor of Science in Business Administration";
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSBA, 1)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSBA, 2)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSBA, 3)));
            studGrades.push_back(studentt);
        }
        sqlite3_finalize(selBSBA);

        const char* selectBSA = "SELECT studentID, "
                    "testSub1, "
                    "testSub2, "
                    "testSub3 "
                    "FROM BSA;";
        sqlite3_stmt *selBSA;
        rc = sqlite3_prepare_v2(db, selectBSA, -1, &selBSA, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Error SELECT statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(selBSA);
            sqlite3_close(db);
        }
        while (sqlite3_step(selBSA) == SQLITE_ROW)
        {
            studAcadPerf studentt;
            studentt.studId = reinterpret_cast<const char*>(sqlite3_column_text(selBSA, 0));
            studentt.course = "Bachelor of Science in Agriculture";
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSA, 1)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSA, 2)));
            studentt.grades.push_back(static_cast<float>(sqlite3_column_double(selBSA, 3)));
            studGrades.push_back(studentt);
        }
        sqlite3_finalize(selBSA);
        sqlite3_close(db);
    }
    public:
    void runCreateDB(){
        createDB();
        createGradingSheets();
    }
    void runPush2DB(){
        push2Dbase();
    }
    void runPullFDbase(){
        pullFDbase();
    }
    int runGetStudentCount(string what){
        return getStudentCount(what);
    }
    void runPushGrades(){
        pushGrades();
    }
    void runPullGrades(){
        pullGrades();
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
                string findStudID;
                bool find;
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
                    
                    cout << studentNum - 1;
                    // to use studInfo[index].1ststruct.nestedstruct;
                    cout << "|-----------Student Registered-----------|\n";
                    printStudentInfo(studentNum - 1);
                    cout << "|----------------------------------------|\n";
                    break;
                case 2:
                    cout << "|--------Enroll Student in Course--------|\n";
                    cout << "Enter Student ID: ";
                    cin >> findStudID;
                    
                        for (int i = 0; i < studInfo.size(); i++)
                        {
                            if (studInfo[i].studentID == findStudID)
                            {
                                if (studInfo[i].courseEnrolled == "Not Enrolled")
                                {
                                    int selections;
                                    cout << "|------------Available Courses-----------|\n";
                                    cout << "| 1. Bachelor of Science in Information Technology\n";
                                    cout << "| 2. Bachelor of Science in Business Administration\n";
                                    cout << "| 3. Bachelor of Science in Agriculture\n";
                                    cout << "|----------------------------------------|\n";
                                    cin >> selections;
                                    switch (selections)
                                    {
                                    case 1:
                                        if (studCap != 0)
                                        {
                                            studAcadPerf studentGrades;
                                            studCap[0]--;
                                            studInfo[i].courseEnrolled = "Bachelor of Science in Information Technology";
                                            studentGrades.studId = studInfo[i].studentID;
                                            studentGrades.course = "Bachelor of Science in Information Technology";
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studGrades.push_back(studentGrades);
                                            cout << "|----------------------------------------|\n";
                                            cout << "|---Student Officialy Enrolled on BSIT---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                        }
                                        break;
                                    case 2:
                                        if (studCap != 0)
                                        {
                                            studAcadPerf studentGrades;
                                            studCap[0]--;
                                            studInfo[i].courseEnrolled = "Bachelor of Science in Business Administration";
                                            studentGrades.studId = studInfo[i].studentID;
                                            studentGrades.course = "Bachelor of Science in Business Administration";
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studGrades.push_back(studentGrades);
                                            cout << "|----------------------------------------|\n";
                                            cout << "|---Student Officialy Enrolled on BSBA---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                        }
                                        break;
                                    case 3:
                                        if (studCap != 0)
                                        {
                                            studAcadPerf studentGrades;
                                            studCap[0]--;
                                            studInfo[i].courseEnrolled = "Bachelor of Science in Agriculture";
                                            studentGrades.studId = studInfo[i].studentID;
                                            studentGrades.course = "Bachelor of Science in Agriculture";
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studentGrades.grades.push_back(0.00);
                                            studGrades.push_back(studentGrades);
                                            cout << "|----------------------------------------|\n";
                                            cout << "|----Student Officialy Enrolled on BSA---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                        }
                                        break;
                                    default:
                                        cout << "|-------------Invalid Input!-------------|\n";
                                        break;
                                    }
                                    find = true;
                                }
                                else if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                {
                                    cout << "|----------------------------------------|\n";
                                    cout << "|--------Student Already Enrolled--------|\n";
                                    cout << "|----------------------------------------|\n";
                                    find = true;
                                }
                            }
                        }
                        if (!find)
                        {
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                        }
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
                                    cin.ignore();
                                    getline(cin, studInfo[i].address);
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
                                for (int i = 0; i < studGrades.size(); i++)
                                {
                                    if (studGrades[i].studId == findID)
                                    {
                                        studGrades.erase(studGrades.begin() + i);
                                    }
                                }
                                studentNum--;
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
            string findID;
            bool found = false;
            cout << "|----------Manage Grades----------|\n";
            cout << "Enter Student ID: ";
            cin >> findID;
            
            for (int i = 0; i < studGrades.size(); i++)
            {
                if (studGrades[i].studId == findID)
                {
                    bool loop = true;
                    while (loop)
                    {
                    found = true;
                    int selection;
                    cout << "|--------------------------------|\n";
                    cout << "| Student ID: " << studGrades[i].studId << endl;
                    cout << "| Course: " << studGrades[i].course << endl;
                    cout << "|--------------------------------|\n\n";
                    cout << "|--------Grade Management--------|\n";
                    cout << "| 1. Add Grade                   |\n";
                    cout << "| 2. Update Grade                |\n";
                    cout << "| 3. Delete Grade                |\n";
                    cout << "| 4. Back                        |\n";
                    cout << "|--------------------------------|\n";
                    cout << "Selection: ";
                    cin >> selection;
                    int subject;
                    float grade;
                    switch (selection)
                    {
                        case 1:
                            if (studGrades[i].course == "Bachelor of Science in Information Technology")
                            {
                                cout << "| 1. CC101: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. CC102: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. GE6: " << studGrades[i].grades[2] << endl;
                            }
                            else if (studGrades[i].course == "Bachelor of Science in Business Administration")
                            {
                                cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                            }
                            else if (studGrades[i].course == "Bachelor of Science in Agriculture")
                            {
                                cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                            }
                                cout << "Enter the subject: ";
                                cin >> subject;
                                if (subject == 1) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[0] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 2) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[1] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 3) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[2] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } 
                                else {
                                    cout << "|-----------Invalid Subject!-----------|\n";
                                    continue;
                                }
                                break;
                            case 2:
                                if (studGrades[i].course == "Bachelor of Science in Information Technology")
                                {
                                    cout << "| 1. CC101: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. CC102: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. GE6: " << studGrades[i].grades[2] << endl;
                                }
                                else if (studGrades[i].course == "Bachelor of Science in Business Administration")
                                {
                                    cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                                }
                                else if (studGrades[i].course == "Bachelor of Science in Agriculture")
                                {
                                    cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                                }
                            cout << "Enter the subject: ";
                            cin >> subject;
                                if (subject == 1) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[0] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 2) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[1] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 3) {
                                    cout << "Enter the grade: ";
                                    cin >> grade;
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[2] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            cin >> grade;
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } 
                                else {
                                    cout << "|---------Invalid Subject!---------|\n";
                                    continue;
                                }                            break;
                        case 3:
                            if (studGrades[i].course == "Bachelor of Science in Information Technology")
                            {
                                cout << "| 1. CC101: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. CC102: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. GE6: " << studGrades[i].grades[2] << endl;
                            }
                            else if (studGrades[i].course == "Bachelor of Science in Business Administration")
                            {
                                cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                            }
                            else if (studGrades[i].course == "Bachelor of Science in Agriculture")
                            {
                                cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                            }
                            cout << "Enter the subject: ";
                            cin >> subject;
                            if (subject == 1) {
                                studGrades[i].grades[0] = 0;
                                cout << "|-----------Grade Deleted!-----------|\n";
                            } else if (subject == 2) {
                                studGrades[i].grades[1] = 0;
                                cout << "|-----------Grade Deleted!-----------|\n";
                            } else if (subject == 3) {
                                studGrades[i].grades[2] = 0;
                                cout << "|-----------Grade Deleted!-----------|\n";
                            } else {
                                cout << "|----------Invalid Subject!----------|\n";
                                continue;
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
            }
            if (!found)
            {
            cout << "|----------------------------------------|\n";
            cout << "|-----------Student Not Found!-----------|\n";
            cout << "|----------------------------------------|\n";
            }
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
                if (sel == 1)
                {
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
                }
                else if (sel == 2)
                {
                    string findID;
                    bool found = false;
                    cout << "|--------Generate Course Schedule--------|\n";
                    cout << "Enter Student ID: ";
                    cin >> findID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            if (studInfo[i].courseEnrolled != "Not Enrolled")
                            {
                                found = true;
                                string courseEnrolled = studInfo[i].courseEnrolled;
                                cout << "|-----------Course Schedule-------------|\n";
                                cout << "Student ID: " << findID << endl;
                                cout << "Course Enrolled: " << courseEnrolled << endl;
                                cout << "Schedule: ";
                                if (courseEnrolled == "Bachelor of Science in Information Technology")
                                {
                                    cout << "          Monday 8:00 AM - 10:00 AM" << endl;
                                    cout << "          Wednesday 10:00 AM - 12:00 PM" << endl;
                                    cout << "          Friday 1:00 PM - 3:00 PM" << endl;
                                }
                                else if (courseEnrolled == "Bachelor of Science in Business Administration")
                                {
                                    cout << "          Tuesday 8:00 AM - 10:00 AM" << endl;
                                    cout << "          Thursday 10:00 AM - 12:00 PM" << endl;
                                    cout << "          Saturday 1:00 PM - 3:00 PM" << endl;
                                }
                                else if (courseEnrolled == "Bachelor of Science in Agriculture")
                                {
                                    cout << "          Monday 1:00 PM - 3:00 PM" << endl;
                                    cout << "          Wednesday 3:00 PM - 5:00 PM" << endl;
                                    cout << "          Friday 10:00 AM - 12:00 PM" << endl;
                                }
                                cout << "|---------------------------------------|\n";
                            }
                            else
                            {
                                cout << "|---------------------------------------|\n";
                                cout << "|---------Student Not Enrolled!---------|\n";
                                cout << "|---------------------------------------|\n";
                            }
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "|---------------------------------------|\n";
                        cout << "|-----------Student Not Found!----------|\n";
                        cout << "|---------------------------------------|\n";
                    }
                }
                else if (sel == 3)
                {
                    string findID;
                    bool found = false;
                    cout << "|--------Generate Academic Performance Report--------|\n";
                    cout << "Enter Student ID: ";
                    cin >> findID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            if (studInfo[i].courseEnrolled != "Not Enrolled")
                            {
                                found = true;
                                string courseEnrolled = studInfo[i].courseEnrolled;
                                cout << "|-----------Academic Performance Report-------------|\n";
                                cout << "Student ID: " << findID << endl;
                                cout << "Course Enrolled: " << courseEnrolled << endl;
                                cout << "Grades: ";
                                if (studGrades[i].course == "Bachelor of Science in Information Technology")
                                {
                                    cout << "| 1. CC101: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. CC102: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. GE6: " << studGrades[i].grades[2] << endl;
                                }
                                else if (studGrades[i].course == "Bachelor of Science in Business Administration")
                                {
                                    cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                                }
                                else if (studGrades[i].course == "Bachelor of Science in Agriculture")
                                {
                                    cout << "| 1. Test Subject 1: " << studGrades[i].grades[0] << endl;
                                    cout << "| 2. Test Subject 2: " << studGrades[i].grades[1] << endl;
                                    cout << "| 3. Test Subject 3: " << studGrades[i].grades[2] << endl;
                                }
                            }
                            else
                            {
                                cout << "|----------------------------------------|\n";
                                cout << "|---------Student Not Enrolled!---------|\n";
                                cout << "|----------------------------------------|\n";
                            }
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "|----------------------------------------|\n";
                        cout << "|-----------Student Not Found!-----------|\n";
                        cout << "|----------------------------------------|\n";
                    }
                }
                else if (sel == 4)
                {
                    break;
                }
                else
                {
                    cout << "|-----------Invalid Selection!-----------|\n";
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
    login loginInfo;
    int sel;
    char selC;    
    string admin, pass;
    accessDbase.runCreateDB();
    accessDbase.runPullFDbase();
    studentEnrolled = accessDbase.runGetStudentCount("totalEnrolled");
    if (studentEnrolled > 0)
    {
        accessDbase.runPullGrades();
    }
    studentNum = accessDbase.runGetStudentCount("studentNumbers");
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
            cout << "|--------Admin Previlage Required--------|\n";
            cout << "| Username: ";
            cin >> admin;
            cout << "| Password: ";
            cin >> pass;
            if (admin == loginInfo.getUsername() && pass == loginInfo.getPassword())
            {
                process.runStdRecords();                
            }
            else if(admin != loginInfo.getUsername() || pass != loginInfo.getPassword())
            {
                cout << "|---Username and Password did not match--|\n";
            }           
                break;
            case 3:
            cout << "|--------Admin Previlage Required--------|\n";
            cout << "| Username: ";
            cin >> admin;
            cout << "| Password: ";
            cin >> pass;
            if (admin == loginInfo.getUsername() && pass == loginInfo.getPassword())
            {
                process.runMngGrades();                
            }
            else if(admin != loginInfo.getUsername() || pass != loginInfo.getPassword())
            {
                cout << "|---Username and Password did not match--|\n";
            }           
                break;
            case 4:
            cout << "|--------Admin Previlage Required--------|\n";
            cout << "| Username: ";
            cin >> admin;
            cout << "| Password: ";
            cin >> pass;
            if (admin == loginInfo.getUsername() && pass == loginInfo.getPassword())
            {
                process.runGenReports();                
            }
            else if(admin != loginInfo.getUsername() || pass != loginInfo.getPassword())
            {
                cout << "|---Username and Password did not match--|\n";
            }           
                break;
            case 5:
                loop = false;
                break;
            default:
                cout << "|-----------Invalid Selection!-----------|\n";
                break;
            }
    }
    remove("Student Information.db");
    accessDbase.runCreateDB();
    accessDbase.runPush2DB();
    if (accessDbase.runGetStudentCount("totalEnrolled") > 0 || studentEnrolled > 0)
    {
        accessDbase.runPushGrades();
    }    
    return 0;
}