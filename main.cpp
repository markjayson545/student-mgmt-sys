#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sqlite3.h>
#include <conio.h>
#include <limits>
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

int errorInputHandlingInt(){
    int input;
    bool validType = false;
    while (!validType){
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n|-----------Invalid Selection!-----------|\n";
            cout << "| Selection: ";
        }
        else
        {
            validType = true;
        }
    }
    return input;
}
long long int errorInputHandlingLong(){
    long long int input;
    bool validType = false;
    while (!validType){
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n|-----------Invalid Selection!-----------|\n";
            cout << "| Selection: ";
        }
        else
        {
            validType = true;
        }
    }
    return input;
}
float errorInputHandlingFloat(){
    float input;
    bool validType = false;
    while (!validType){
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n|-----------Invalid Selection!-----------|\n";
            cout << "| Selection: ";
        }
        else
        {
            validType = true;
        }
    }
    return input;
}
char errorInputHandlingChar(){
    char input;
    bool validType = false;
    while (!validType){
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n|-----------Invalid Selection!-----------|\n";
            cout << "| Selection: ";
        }
        else
        {
            validType = true;
        }
    }
    return input;
}

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

class txtBaseAccess{
    private:
    void pushStudInfoToTxt() {
        ofstream studInfoTxt("Student Information.txt");
        if (studInfoTxt.is_open())
        {
            for (int i = 0; i < studInfo.size(); i++)
            {
                studInfoTxt << "Last Name: " << studInfo[i].fullName.lastName << endl;
                studInfoTxt << "First Name: " << studInfo[i].fullName.firstName << endl;
                studInfoTxt << "Middle Name: " << studInfo[i].fullName.middleName << endl;
                studInfoTxt << "BirthMonth: " << studInfo[i].birthDate.month << endl;
                studInfoTxt << "BirthDay: " << studInfo[i].birthDate.day << endl;
                studInfoTxt << "BirthYear: " << studInfo[i].birthDate.year << endl;
                studInfoTxt << "Sex: " << studInfo[i].sex << endl;
                studInfoTxt << "Phone Number: " << studInfo[i].phoneNumber << endl;
                studInfoTxt << "Email: " << studInfo[i].email << endl;
                studInfoTxt << "Address: " << studInfo[i].address << endl;
                studInfoTxt << "Course Enrolled: " << studInfo[i].courseEnrolled << endl;
                studInfoTxt << "Student ID: " << studInfo[i].studentID << endl;
                studInfoTxt << endl;
            }
            studInfoTxt.close();
        }
        else
        {
            cout << "|------Error Opening Student Information File------|\n";
        }
    }
    void pullStudInfoToTxt() {
        ifstream studInfoTxt("Student Information.txt");
        if (studInfoTxt.is_open())
        {
            string line;
            while (getline(studInfoTxt, line))
            {
                if (!line.empty())
                {
                    studentInfo student;
                    student.fullName.lastName =  line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.fullName.firstName =  line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.fullName.middleName =  line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.birthDate.month = stoi(line.substr(line.find(":") + 2));
                    getline(studInfoTxt, line);
                    student.birthDate.day = stoi(line.substr(line.find(":") + 2));
                    getline(studInfoTxt, line);
                    student.birthDate.year = stoi(line.substr(line.find(":") + 2));
                    getline(studInfoTxt, line);
                    student.sex = line.substr(line.find(":") + 2)[0];
                    getline(studInfoTxt, line);
                    student.phoneNumber = stoll(line.substr(line.find(":") + 2));
                    getline(studInfoTxt, line);
                    student.email = line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.address = line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.courseEnrolled = line.substr(line.find(":") + 2);
                    getline(studInfoTxt, line);
                    student.studentID = line.substr(line.find(":") + 2);
                    studInfo.push_back(student);
                }
            }
            studInfoTxt.close();
        }
        else{
            cout << "|------Error Opening Student Information File------|\n";
        }
    }
    void pushStudGradesToTxt() {
        ofstream studGradesTxt("Student Grades.txt");
        if (studGradesTxt.is_open())
        {
            for (int i = 0; i < studGrades.size(); i++)
            {
                studGradesTxt << "Student ID: " << studGrades[i].studId << endl;
                studGradesTxt << "Course: " << studGrades[i].course << endl;
                    for (int i = 0; i < studGrades.size(); i++)
                    {
                        if(studGrades[i].course == "Bachelor of Science in Information Technology")
                        {
                            studGradesTxt << "CC101: " << studGrades[i].grades[0] << endl;
                            studGradesTxt << "CC102: " << studGrades[i].grades[1] << endl;
                            studGradesTxt << "GE6: " << studGrades[i].grades[2] << endl;
                        }
                        else if(studGrades[i].course == "Bachelor of Science in Business Administration")
                        {
                            studGradesTxt << "Test Subject 1: " << studGrades[i].grades[0] << endl;
                            studGradesTxt << "Test Subject 2: " << studGrades[i].grades[1] << endl;
                            studGradesTxt << "Test Subject 3: " << studGrades[i].grades[2] << endl;
                        }
                        else if(studGrades[i].course == "Bachelor of Science in Agriculture")
                        {
                            studGradesTxt << "Test Subject 1: " << studGrades[i].grades[0] << endl;
                            studGradesTxt << "Test Subject 2: " << studGrades[i].grades[1] << endl;
                            studGradesTxt << "Test Subject 3: " << studGrades[i].grades[2] << endl;
                        }
                    }
            }
            studGradesTxt.close();
        }
        else
        {
            cout << "|------Error Opening Student Grades File------|\n";
        }
    }
    void pullStudGradesToTxt() {
        ifstream studGradesTxt("Student Grades.txt");
        if (studGradesTxt.is_open())
        {
            string line;
            while (getline(studGradesTxt, line))
            {
                if (!line.empty())
                {
                    studAcadPerf student;
                    student.studId = line.substr(line.find(":") + 2);
                    getline(studGradesTxt, line);
                    student.course = line.substr(line.find(":") + 2);
                    if (student.course == "Bachelor of Science in Information Technology")
                    {
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                    }
                    else if (student.course == "Bachelor of Science in Business Administration")
                    {
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                    }
                    else if (student.course == "Bachelor of Science in Agriculture")
                    {
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                        getline(studGradesTxt, line);
                        student.grades.push_back(stof(line.substr(line.find(":") + 2)));
                    }
                    studGrades.push_back(student);
                }
            }
            studGradesTxt.close();
        }
        else
        {
            cout << "|------Error Opening Student Grades File------|\n";
        }
    }
    int getStudentCount(string what){
        if (what == "studentNumbers")
        {
            return studInfo.size();
        }
        else if (what == "BSITenrolled")
        {
            int count = 0;
            for (int i = 0; i < studInfo.size(); i++)
            {
                if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology")
                {
                    count++;
                }
            }
            return count;
        }
        else if (what == "BSBAenrolled")
        {
            int count = 0;
            for (int i = 0; i < studInfo.size(); i++)
            {
                if (studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration")
                {
                    count++;
                }
            }
            return count;
        }
        else if (what == "BSAenrolled")
        {
            int count = 0;
            for (int i = 0; i < studInfo.size(); i++)
            {
                if (studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                {
                    count++;
                }
            }
            return count;
        }
        else if(what == "notEnrolled"){
            int count = 0;
            for (int i = 0; i < studInfo.size(); i++)
            {
                if (studInfo[i].courseEnrolled == "Not Enrolled")
                {
                    count++;
                }
            }
            return count;
        }
        else if (what == "totalEnrolled")
        {
            int count = 0;
            for (int i = 0; i < studInfo.size(); i++)
            {
                if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology" ||
                    studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration" ||
                    studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                {
                    count++;
                }
            }
            return count;
        }
        return 0;
    }
    public:
    void initialize(){
        ifstream openStudInfo("Student Information.txt");
        if (openStudInfo) {
            openStudInfo.close();
            pullStudInfoToTxt();
        } else {
            ofstream createStudInfo("Student Information.txt");
            createStudInfo.close();
        }
        ifstream openStudGrades("Student Grades.txt");
        if (openStudGrades) {
            openStudGrades.close();
            pullStudGradesToTxt();
        } else {
            ofstream createStudGrades("Student Grades.txt");
            createStudGrades.close();
        }
        studentNum = getStudentCount("studentNumbers");
        studentEnrolled = getStudentCount("totalEnrolled");
        studCap[0] -= getStudentCount("BSITenrolled");
        studCap[1] -= getStudentCount("BSBAenrolled");
        studCap[2] -= getStudentCount("BSAenrolled");
    }
    void finalize(){
        if (studInfo.size() > 0)
        {
            remove("Student Information.txt");
            pushStudInfoToTxt();
        }
        if (getStudentCount("totalEnrolled") > 0)
        {
            remove("Student Grades.txt");
            pushStudGradesToTxt();
        }
    }
    int runGetStudentCount(string what){
        return getStudentCount(what);
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
    void initialize(){
        createDB();
        createGradingSheets();
        pullFDbase();
        studCap[0] -= getStudentCount("BSITenrolled");
        studCap[1] -= getStudentCount("BSBAenrolled");
        studCap[2] -= getStudentCount("BSAenrolled");
        studentEnrolled = getStudentCount("totalEnrolled");
        if (studentEnrolled > 0)
        {
            pullGrades();
        }
        studentNum = getStudentCount("studentNumbers");
    }
    void finalize(){
        remove("Student Information.db");
        createDB();
        createGradingSheets();
        push2Dbase();
        if (getStudentCount("totalEnrolled") > 0 || studentEnrolled > 0)
        {
            pushGrades();
        }    
    }
    int runGetStudentCount(string what){
        return getStudentCount(what);
    }
};

class processing: public login{
    private:
        void printStudentInfo(int target){
            cout << " Student ID      :: " << studInfo[target].studentID << endl;
            cout << " Full Name       :: " << studInfo[target].fullName.lastName << ", " << studInfo[target].fullName.firstName << ' ' << studInfo[target].fullName.middleName << endl;
            cout << " Sex             :: " << studInfo[target].sex << endl;
            cout << " Date of Birth   :: " << studInfo[target].birthDate.month << '/' << studInfo[target].birthDate.day << '/' << studInfo[target].birthDate.year << endl;
            cout << " Phone Number    :: " << studInfo[target].phoneNumber << endl;
            cout << " Email           :: " << studInfo[target].email << endl;
            cout << " Address         :: " << studInfo[target].address << endl;
            cout << " Course Enrolled :: " << studInfo[target].courseEnrolled << endl;
        }
        void stdRegNenroll(){
            int sel;
            bool loop = true;
            while (loop)
            {
                string findStudID;
                bool find;
                studentInfo student;
                system("cls");
                cout << "|----Student Registration & Enrollment---|\n";
                cout << "| 1. Register New Student                |\n";
                cout << "| 2. Enroll Student in Course            |\n";
                cout << "| 3. Drop Course                         |\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "| Selection: ";
                sel = errorInputHandlingInt();
                switch (sel)
                {
                case 1:
                system("cls");
                    cout << "|----------Register New Student----------|\n";
                    // get full name
                    cout << "| Enter Last Name: ";
                    cin.ignore(); //ignore the line above
                    getline(cin, student.fullName.lastName);
                    cout << "| Enter First Name: ";
                    getline(cin, student.fullName.firstName);
                    cout << "| Enter Middle Name: ";
                    getline(cin, student.fullName.middleName);
                        //get sex orientation and retyrn if invalid
                        do
                        {
                            cout << "| Enter Sex (M/F): ";
                            student.sex = errorInputHandlingChar(); 
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
                            cout << "| Enter Birthdate:" << endl << "| Month (1-12): ";
                            student.birthDate.month = errorInputHandlingInt();
                                if (student.birthDate.month > 12 || student.birthDate.month <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
                                }                                       
                        } while (student.birthDate.month > 12 || student.birthDate.month <= 0);
                        do
                        {
                            cout << "| Day (1-31): ";
                            student.birthDate.day = errorInputHandlingInt();
                                if (student.birthDate.day > 31 || student.birthDate.day <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
                                }
                        } while (student.birthDate.day > 31 || student.birthDate.day <= 0);
                        do
                        {
                            cout << "| Year (~2024): ";
                            student.birthDate.year = errorInputHandlingInt();
                                if (student.birthDate.year <= 1900 || student.birthDate.year <= 1900 || student.birthDate.day <= 0)
                                {
                                        cout << "|-------------Invalid Input!-------------|\n";
                                }
                        } while (student.birthDate.year > 2024 || student.birthDate.year <= 1900 || student.birthDate.day <= 0);
                        cout << "| Enter Phone Number: ";
                        student.phoneNumber = errorInputHandlingLong();
                        cout << "| Enter Email Address: ";
                        cin.ignore();
                        getline(cin, student.email);
                        cout << "| Enter Address: ";
                        cin.ignore(); // ignore above nanaman
                        getline(cin, student.address);
                        studentNum++;
                        if (studentNum > 1) {
                            string previousStudentID = studInfo[studentNum - 2].studentID;
                            int lastDashIndex = previousStudentID.find_last_of("-");
                            string previousNumber = previousStudentID.substr(lastDashIndex + 1);
                            int nextNumber = stoi(previousNumber) + 1;
                            student.studentID = previousStudentID.substr(0, lastDashIndex + 1) + to_string(nextNumber);
                        } else {
                            student.studentID = to_string(year) + "-SC-" + to_string(studentNum);
                        }
                        student.courseEnrolled = "Not Enrolled";
                        // push data to vector
                        studInfo.push_back(student);
                        // to use studInfo[index].1ststruct.nestedstruct;
                        system("cls");
                        cout << "|-----------Student Registered-----------|\n";
                        printStudentInfo(studentNum - 1);
                    cout << "|----------------------------------------|\n";
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    cout << "|--------Enroll Student in Course--------|\n";
                    cout << "| Enter Student ID: ";
                    cin.ignore();
                    getline(cin, findStudID);
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
                                    cout << "| Selection: ";
                                    selections = errorInputHandlingInt();
                                    switch (selections)
                                    {
                                    case 1:
                                        if (studCap[0] != 0)
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
                                            system("cls");
                                            cout << "|----------------------------------------|\n";
                                            cout << "|---Student Officialy Enrolled on BSIT---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                            system("pause");
                                            system("cls");
                                        }
                                        else
                                        {
                                            system("cls");
                                            cout << "|-------------Course Full!---------------|\n";
                                            system("pause");
                                            system("cls");
                                        }
                                        break;
                                    case 2:
                                        if (studCap[1] != 0)
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
                                            system("cls");
                                            cout << "|----------------------------------------|\n";
                                            cout << "|---Student Officialy Enrolled on BSBA---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                            system("pause");
                                            system("cls");
                                        }
                                        else
                                        {
                                            system("cls");
                                            cout << "|-------------Course Full!---------------|\n";
                                            system("pause");
                                            system("cls");
                                        }
                                        break;
                                    case 3:
                                        if (studCap[2] != 0)
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
                                            system("cls");
                                            cout << "|----------------------------------------|\n";
                                            cout << "|----Student Officialy Enrolled on BSA---|\n";
                                            cout << "|----------------------------------------|\n";
                                            studentEnrolled++;
                                            system("pause");
                                            system("cls");
                                        }
                                        else
                                        {
                                            system("cls");
                                            cout << "|-------------Course Full!---------------|\n";
                                            system("pause");
                                            system("cls");
                                        }
                                        break;
                                    default:
                                        system("cls");
                                        cout << "|-------------Invalid Input!-------------|\n";
                                        system("pause");
                                        system("cls");
                                        break;
                                    }
                                    find = true;
                                }
                                else if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                {
                                    system("cls");
                                    cout << "|----------------------------------------|\n";
                                    cout << "|--------Student Already Enrolled--------|\n";
                                    cout << "|----------------------------------------|\n";
                                    find = true;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        if (!find)
                        {
                            system("cls");
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                            system("pause");
                            system("cls");
                        }
                    break;
                case 3:
                    system("cls");
                    cout << "|--------------Drop Course---------------|\n";
                    cout << "| Enter Student ID: ";
                    cin.ignore();
                    getline(cin, findStudID);
                        for (int i = 0; i < studInfo.size(); i++)
                        {
                            if (studInfo[i].studentID == findStudID)
                            {
                                if (studInfo[i].courseEnrolled == "Not Enrolled")
                                {
                                    system("cls");
                                    cout << "|----------------------------------------|\n";
                                    cout << "|----Student Not Enrolled in any Course---|\n";
                                    cout << "|----------------------------------------|\n";
                                    system("pause");
                                    system("cls");
                                }
                                else if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration" ||
                                        studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                {
                                    studInfo[i].courseEnrolled = "Not Enrolled";
                                    system("cls");
                                        for (int k = 0; k < studGrades.size(); k++)
                                        {
                                            if (studGrades[k].studId == findStudID)
                                            {
                                                studGrades.erase(studGrades.begin() + k);
                                            }
                                        }
                                    cout << "|----------------------------------------|\n";
                                    cout << "|----Student Officialy Dropped Course----|\n";
                                    cout << "|----------------------------------------|\n";
                                    studentEnrolled--;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                    break;
                case 4:
                loop = false;
                    break;
                default:
                    system("cls");
                    cout << "|-----------Invalid Selection!-----------|\n";
                    system("pause");
                    system("cls");
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
                system("cls");
                cout << "|---------Manage Student Records---------|\n";
                cout << "| 1. View Student Details                |\n";
                cout << "| 2. Edit Student Details                |\n";
                cout << "| 3. Delete Student Record               |\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "| Selection: ";
                sel = errorInputHandlingInt();
                switch (sel)
                {
                case 1:
                system("cls");
                cout << "|----------View Student Details----------|\n";
                cout << "| Enter Student Id: ";
                cin.ignore();
                getline(cin, findID);
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            cout << "|----------------------------------------|\n";
                            printStudentInfo(i);
                            found = true;
                            cout << "|----------------------------------------|\n";
                            system("pause");
                            system("cls");
                        }
                    }
                        if (!found)
                        {
                            system("cls");
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                            system("pause");
                            system("cls");
                        }
                    break;
                case 2:
                int selection;
                system("cls");
                cout << "Enter Student ID to edit: ";
                cin.ignore();
                getline(cin, findID);
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            bool looop = true;
                            while (looop){
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
                            selection = errorInputHandlingInt();
                                switch (selection)
                                {
                                case 1:
                                system("cls");
                                cout << "|------------Change Full Name------------|\n";
                                cout << "a. Last Name   :: ";
                                cin.ignore();
                                getline(cin, studInfo[i].fullName.lastName);
                                cout << "b. First Name  :: ";
                                getline(cin, studInfo[i].fullName.firstName);
                                cout << "c. Middle Name :: ";
                                getline(cin, studInfo[i].fullName.middleName);
                                cout << "|-----FullName modified successfully-----|\n";
                                system("pause");
                                system("cls");
                                    break;
                                case 2:
                                system("cls");
                                    cout << "|---------------Change Sex---------------|\n";
                                    do
                                    {
                                        cout << "Enter Sex (M/F): ";
                                        studInfo[i].sex = errorInputHandlingChar();
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
                                                system("cls");
                                                cout << "|-------------Invalid Input!-------------|";
                                                system("pause");
                                                system("cls");
                                            }
                                    } while (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F');
                                    system("cls");
                                    cout << "|--------Sex Successfully Changed--------|\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                case 3:
                                system("cls");
                                cout << "|------------Change BirthDate------------|\n";
                                    do
                                    {
                                        cout << "| Month (1-12)   :: ";
                                        studInfo[i].birthDate.month = errorInputHandlingInt();
                                            if (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }                                       
                                    } while (studInfo[i].birthDate.month > 12 || studInfo[i].birthDate.month <= 0);
                                    do
                                    {
                                        cout << "| Day            :: ";
                                        studInfo[i].birthDate.day = errorInputHandlingInt();
                                            if (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }
                                    } while (studInfo[i].birthDate.day > 31 || studInfo[i].birthDate.day <= 0);
                                    do
                                    {
                                        cout << "| Year           :: ";
                                        studInfo[i].birthDate.year = errorInputHandlingInt();
                                            if (studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0)
                                            {
                                                cout << "|-------------Invalid Input!-------------|";
                                            }
                                    } while (studInfo[i].birthDate.year > 2024 || studInfo[i].birthDate.year <= 1900 || studInfo[i].birthDate.day <= 0);                            
                                            cout << "|-----Birthdate changed Successfully-----|\n";
                                            system("pause");
                                            system("cls");
                                    break;
                                case 4:
                                system("cls");
                                    cout << "|-----------Change PhoneNumber-----------|\n";
                                    cout << "Phone Number: ";
                                    studInfo[i].phoneNumber = errorInputHandlingLong();
                                    cout << "|----PhoneNumber Changed Successfully----|\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                case 5:
                                system("cls");
                                    cout << "|----------Change Email Address----------|\n";
                                    cout << "Email Address: ";
                                    cin.ignore();
                                    getline(cin, studInfo[i].email);
                                    cout << "|---Email Address Changed Successfully---|\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                case 6:
                                system("cls");
                                    cout << "|-------------Change Address-------------|\n";
                                    cout << "Address: ";
                                    cin.ignore();
                                    getline(cin, studInfo[i].address);
                                    cout << "|------Address Changed Successfully------|\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                case 7:
                                    for (int j = 0; j < studGrades.size(); j++)
                                    {
                                        if (findID == studGrades[j].studId)
                                        {
                                            system("cls");
                                            int selectCourse;
                                            cout << "|---------Change Course Enrolled---------|\n";
                                            cout << "| Course Enrolled: " << studInfo[j].courseEnrolled << endl;
                                            cout << "|----------------------------------------|\n";
                                            cout << "| 1. Bachelor of Science in Information Technology\n";
                                            cout << "| 2. Bachelor of Science in Business Administration\n";
                                            cout << "| 3. Bachelor of Science in Agriculture\n";
                                            cout << "| 4. Cancel\n";
                                            cout << "|----------------------------------------|\n";
                                            bool changeCourse = true;
                                            while(changeCourse)
                                            {
                                                cout << "| Selection: ";
                                                selectCourse = errorInputHandlingInt();
                                                bool ifEnrolled = false;
                                                if (selectCourse == 1)
                                                {
                                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology")
                                                    {
                                                        cout << "|---Student Already Enrolled in BSIT---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration")
                                                    {
                                                        studCap[0]++;
                                                        studCap[1]--;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Information Technology";
                                                        studGrades[j].course = "Bachelor of Science in Information Technology";
                                                        cout << "|---Student Enrolled in BSIT Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                                    {
                                                        studCap[0]++;
                                                        studCap[2]--;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Information Technology";
                                                        studGrades[j].course = "Bachelor of Science in Information Technology";
                                                        cout << "|---Student Enrolled in BSIT Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                }
                                                else if (selectCourse == 2)
                                                {
                                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration")
                                                    {
                                                        cout << "|---Student Already Enrolled in BSBA---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology")
                                                    {
                                                        studCap[0]--;
                                                        studCap[1]++;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Business Administration";
                                                        studGrades[j].course = "Bachelor of Science in Business Administration";
                                                        cout << "|---Student Enrolled in BSBA Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                                    {
                                                        studCap[1]++;
                                                        studCap[2]--;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Business Administration";
                                                        studGrades[j].course = "Bachelor of Science in Business Administration";
                                                        cout << "|---Student Enrolled in BSBA Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                }
                                                else if(selectCourse == 3)
                                                {
                                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                                    {
                                                        cout << "|---Student Already Enrolled in BSA---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology")
                                                    {
                                                        studCap[0]--;
                                                        studCap[2]++;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Agriculture";
                                                        studGrades[j].course = "Bachelor of Science in Agriculture";
                                                        cout << "|---Student Enrolled in BSA Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                    else if (studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration")
                                                    {
                                                        studCap[1]--;
                                                        studCap[2]++;
                                                        studInfo[i].courseEnrolled = "Bachelor of Science in Agriculture";
                                                        studGrades[j].course = "Bachelor of Science in Agriculture";
                                                        cout << "|---Student Enrolled in BSA Successfully---|\n";
                                                        ifEnrolled = true;
                                                        changeCourse = false;
                                                    }
                                                }
                                                else if (selectCourse == 4)
                                                {
                                                    changeCourse = false;
                                                }
                                                else{
                                                    cout << "|-----------Invalid Selection!-----------|\n";
                                                }
                                            }
                                            cout << "|--Course Enrolled Changed Successfully--|\n";
                                            system("pause");
                                            system("cls");
                                        }
                                        else
                                        {
                                            system("cls");
                                            cout << "|-----------Student Not Enrolled!-----------|\n";
                                            system("pause");
                                            system("cls");
                                        }
                                    }                               
                                    break;
                                case 8:
                                    looop = false;
                                    break;
                                default:
                                    system("cls");
                                    cout << "|-----------Invalid Selection!-----------|\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                            }
                        }
                    }
                        if (!found)
                        {
                            system("cls");
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                            system("pause");
                            system("cls");  
                        }
                    break;
                case 3:
                system("cls");
                char delet3;
                cout << "|----------Delete Student Record---------|\n";
                cout << "| Enter Student ID: ";
                cin.ignore();
                getline(cin, findID);
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findID)
                        {
                            printStudentInfo(i);
                            found = true;
                            cout << "Do you really want to delete this student record (Y/N)?: ";
                            delet3 = errorInputHandlingChar();
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
                            system("cls");
                            cout << "|----------------------------------------|\n";
                            cout << "|-----------Student Not Found!-----------|\n";
                            cout << "|----------------------------------------|\n";
                            system("pause");
                            system("cls");
                        }

                    break;
                case 4:
                loop = false;
                    break;
                default:
                system("cls");
                cout << "|-----------Invalid Selection!-----------|\n";
                system("pause");
                system("cls");
                    break;
                }
            }
        }
        void mngGrades(){
            string findID;
            bool found = false;
            system("cls");
            cout << "|----------Manage Grades----------|\n";
            cout << "Enter Student ID: ";
            cin.ignore();
            getline(cin, findID);
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
                    selection = errorInputHandlingInt();
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
                                cout << "| Enter the subject: ";
                                subject = errorInputHandlingInt();
                                if (subject == 1) {
                                    cout << "| Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[0] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 2) {
                                    cout << "Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[1] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 3) {
                                    cout << "Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[2] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                    system("pause");
                                    system("cls");
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
                            subject = errorInputHandlingInt();
                                if (subject == 1) {
                                    cout << "Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[0] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 2) {
                                    cout << "Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[1] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
                                        }
                                    }
                                    cout << "|-----------Grade Added!-----------|\n";
                                } else if (subject == 3) {
                                    cout << "Enter the grade: ";
                                    grade = errorInputHandlingFloat();
                                    while (true)
                                    {
                                        if (grade >= 1.0 && grade <= 5.0) {
                                            studGrades[i].grades[2] = grade;
                                            break;
                                        } else {
                                            cout << "|-----------Invalid Grade!-----------|\n";
                                            cout << "Enter the grade: ";
                                            grade = errorInputHandlingFloat();
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
                            cout << "| Enter the subject: ";
                            subject = errorInputHandlingInt();
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
                system("cls");
                string username, password;
                cout << "|------------Generate Reports------------|\n";
                cout << "| 1. Generate Student List               |\n";
                cout << "| 2. Generate Course Schedule            |\n";
                cout << "| 3. Generate Academic Performance Report|\n";
                cout << "| 4. Back                                |\n";
                cout << "|----------------------------------------|\n";
                cout << "Selection: ";
                sel = errorInputHandlingInt();
                if (sel == 1)
                {
                    system("cls");
                    cout << "|----------------------------------------|\n";
                    cout << "|--------Admin Previlage Required--------|\n";
                    cout << "| Username: ";
                    cin.ignore();
                    getline(cin, username);
                    cout << "| Password: ";
                    password = "";
                    char ch;
                    while ((ch = _getch()) != '\r')
                    {
                        password.push_back(ch);
                        cout << '*';
                    }
                    if (username == getUsername() && password == getPassword())
                    {
                        system("cls");
                        if (studInfo.size() <= 0)
                        {
                            cout << "|----------------------------------------|\n";
                            cout << "|---------No Students Registered---------|\n";
                            cout << "|----------------------------------------|\n";
                        }
                        else
                        {
                            cout << "|--------------Student List--------------|\n";
                            cout << "|----------------------------------------|\n";
                            cout << "| BSIT Students: \n";
                                for (int i = 0; i < studInfo.size(); i++)
                                {
                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Information Technology")
                                    {
                                        cout << "| " << studInfo[i].studentID << " :: ";
                                        cout << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                                    }
                                }
                            cout << "|----------------------------------------|\n";
                            cout << "| BSBA Students: \n";
                                for (int i = 0; i < studInfo.size(); i++)
                                {
                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Business Administration")
                                    {
                                        cout << "| " << studInfo[i].studentID << " :: ";
                                        cout << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                                    }
                                }
                            cout << "|----------------------------------------|\n";
                            cout << "| BSA Students: \n";
                                for (int i = 0; i < studInfo.size(); i++)
                                {
                                    if (studInfo[i].courseEnrolled == "Bachelor of Science in Agriculture")
                                    {
                                        cout << "| " << studInfo[i].studentID << " :: ";
                                        cout << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                                    }
                                }
                            cout << "|----------------------------------------|\n";
                            cout << "| Not Enrolled: \n";
                                for (int i = 0; i < studInfo.size(); i++)
                                {
                                    if (studInfo[i].courseEnrolled == "Not Enrolled")
                                    {
                                        cout << "| " << studInfo[i].studentID << " :: ";
                                        cout << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                                    }
                                }
                            cout << "|----------------------------------------|\n";
                            txtBaseAccess getNum;
                            cout << "| BSIT Students            :: " << getNum.runGetStudentCount("BSITenrolled") << endl;
                            cout << "| BSBA Students            :: " << getNum.runGetStudentCount("BSBAenrolled") << endl;
                            cout << "| BSA Students             :: " << getNum.runGetStudentCount("BSAenrolled") << endl;
                            cout << "| Not Enrolled             :: " << getNum.runGetStudentCount("notEnrolled") << endl;
                            cout << "| Total Number of Students :: " << studentNum << endl;
                            cout << "|----------------------------------------|\n";
                        }
                        system("pause");
                        system("cls");
                    }
                    else
                    {
                        system("cls");
                        cout << "|----------------------------------------|\n";
                        cout << "|--------Admin Previlage Denied----------|\n";
                        cout << "|----------------------------------------|\n";
                        system("pause");
                        system("cls");
                    }
                }
                else if (sel == 2)
                {
                    system("cls");
                    string findID;
                    bool found = false;
                    cout << "|--------Generate Course Schedule--------|\n";
                    cout << "| Enter Student ID: ";
                    cin.ignore();
                    getline(cin, findID);
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
                                cout << "Schedule: \n";
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
                    system("pause");
                    system("cls");
                }
                else if (sel == 3)
                {
                    system("cls");
                    string findID;
                    bool found = false;
                    cout << "|--------Generate Academic Performance Report--------|\n";
                    cout << "| Enter Student ID: ";
                    cin.ignore();
                    getline(cin, findID);
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
                                cout << "Grades: " << endl;
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
                    system("pause");
                    system("cls");
                }
                else if (sel == 4)
                {
                    break;
                }
                else
                {
                    system("cls");
                    cout << "|-----------Invalid Selection!-----------|\n";
                    system("pause");
                    system("cls");
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
    // dBaseAccess/txtBaseAccess to change database type
    dBaseAccess accessDbase;
    login loginInfo;
    accessDbase.initialize();
    string admin, pass;
    bool loop = true;
    while (loop)
    {
        system("cls");
        cout << "|--------Student Management System-------|\n";
        cout << "|------------------Menu------------------|\n";
        cout << "| 1. Student Registration and Enrollment |\n";
        cout << "| 2. Manage Student Records              |\n";
        cout << "| 3. Manage Student Perfomance           |\n";
        cout << "| 4. Generate Reports                    |\n";
        cout << "| 5. Exit                                |\n";
        cout << "|----------------------------------------|\n";
        cout << "Selection: ";
        switch (errorInputHandlingInt())
            {
                case 1:
                    process.runStdRegEnroll();
                    break;
                case 2:
                system("cls");
                cout << "|--------Admin Previlage Required--------|\n";
                cout << "| Username: ";
                cin.ignore();
                getline(cin, admin);
                cout << "| Password: ";
                pass = "";
                char c;
                while ((c = _getch()) != '\r') {
                    pass.push_back(c);
                    cout << '*';
                }
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
                system("cls");
                cout << "|--------Admin Previlage Required--------|\n";
                cout << "| Username: ";
                cin.ignore();
                getline(cin, admin);
                cout << "| Password: ";
                pass = "";
                char cr;
                while ((cr = _getch()) != '\r') {
                    pass.push_back(cr);
                    cout << '*';
                }
                if (admin == loginInfo.getUsername() && pass == loginInfo.getPassword())
                {
                    process.runMngGrades();                
                }
                else if(admin != loginInfo.getUsername() || pass != loginInfo.getPassword())
                {
                    system("cls");
                    cout << "|---Username and Password did not match--|\n";
                    system("pause");
                    system("cls");
                }           
                    break;
                case 4:
                process.runGenReports();        
                    break;
                case 5:
                    loop = false;
                    break;
                default:
                    system("cls");
                    cout << "|-----------Invalid Selection!-----------|\n";
                    system("pause");
                    system("cls");
                    break;
            }
    }
    accessDbase.finalize();
    cout << "|----------------------------------------|\n";
    cout << "|-------------Program Exiting------------|\n";
    cout << "|----------------------------------------|\n";
    return 0;
}