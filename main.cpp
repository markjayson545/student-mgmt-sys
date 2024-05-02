#include <iostream>
#include <string>
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
int studentNum = 0;
struct studentInfo
{
    int studentID;
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
    
    public:
    
};

class processing{
    private:

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
                                    cout << "Invalid input!";
                                }                                       
                        } while (student.birthDate.month > 12 || student.birthDate.month <= 0);
                        do
                        {
                            cout << "Day: ";
                            cin >> student.birthDate.day;
                                if (student.birthDate.day > 31 || student.birthDate.day <= 0)
                                {
                                    cout << "Invalid input!";
                                }
                        } while (student.birthDate.day > 31 || student.birthDate.day <= 0);
                        do
                        {
                            cout << "Year: ";
                            cin >> student.birthDate.year;
                                if (student.birthDate.year <= 1900 || student.birthDate.year <= 1900 || student.birthDate.day <= 0)
                                {
                                    cout << "Invalid input!";
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
                        student.studentID = studentNum;
                        student.courseEnrolled = "Not Enrolled";
                    // push data to vector
                    studInfo.push_back(student);
                    // to use studInfo[index].1ststruct.nestedstruct;
                    cout << "-----Student Registered-----" << endl;
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

        void mgmStdRecords(){
            int sel;
            bool loop = true;
            while (loop)
            {
                cout << "1. View Student Details" << endl;
                cout << "2. Edit Student Details" << endl;
                cout << "3. Delete Student Record" << endl;
                cout << "4. Back" << endl;
                cout << "Selection: ";
                cin >> sel;
                switch (sel)
                {
                case 1:
                int findStudID;
                bool found;
                cout << "Enter Student Id: ";
                cin >> findStudID;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findStudID)
                        {
                            cout << "Student ID      :: " << studInfo[i].studentID << endl;
                            cout << "Full Name       :: " << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                            cout << "Sex             :: " << studInfo[i].sex << endl;
                            cout << "Date of Birth   :: " << studInfo[i].birthDate.month << '/' << studInfo[i].birthDate.day << '/' << studInfo[i].birthDate.year << endl;
                            cout << "Phone Number    :: " << studInfo[i].phoneNumber << endl;
                            cout << "Email           :: " << studInfo[i].email << endl;
                            cout << "Address         :: " << studInfo[i].address << endl;
                            cout << "Course Enrolled :: " << studInfo[i].courseEnrolled << endl;
                            found = true;
                        }
                    }
                        if (!found)
                        {
                            cout << "Student Not Found!\n";
                        }
                    break;
                case 2:
                while("true"){
                int findStudID2, selection;
                bool found2;
                cout << "Enter Student ID to edit: ";
                cin >> findStudID2;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findStudID)
                        {
                            cout << "~~ Student ID      :: " << studInfo[i].studentID << endl;
                            cout << "1. Full Name       :: " << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                            cout << "2. Sex             :: " << studInfo[i].sex << endl;
                            cout << "3. Date of Birth   :: " << studInfo[i].birthDate.month << '/' << studInfo[i].birthDate.day << '/' << studInfo[i].birthDate.year << endl;
                            cout << "4. Phone Number    :: " << studInfo[i].phoneNumber << endl;
                            cout << "5. Email           :: " << studInfo[i].email << endl;
                            cout << "6. Address         :: " << studInfo[i].address << endl;
                            cout << "7. Course Enrolled :: " << studInfo[i].courseEnrolled << endl;
                            found2 = true;
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
                                cout << "---Full Name modified successfully---";
                                    break;
                                case 2:
                                    cout << "-----Change Sex-----\n";
                                    do
                                    {
                                        cout << "Enter Sex (M/F): ";
                                        cin >> studInfo[i].sex;
                                            if (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F')
                                            {
                                                cout << "Invalid Input!";
                                            }
                                            
                                    } while (studInfo[i].sex != 'm' && studInfo[i].sex != 'M' && studInfo[i].sex != 'f' && studInfo[i].sex != 'F');
                                    cout << "-----Sex Successfully Changed-----";
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
                                    
                                    break;
                                default:
                                cout << "Invalid Selection!!";
                                    break;
                                }
                        }
                    }
                        if (!found2)
                        {
                            cout << "Student not found!!!\n";
                        }
                }
                    break;
                case 3:
                int findStudID3;
                char delet3;
                bool found3;
                cout << "Enter Student ID: ";
                cin >> findStudID3;
                    for (int i = 0; i < studInfo.size(); i++)
                    {
                        if (studInfo[i].studentID == findStudID3)
                        {
                            cout << "Student ID      :: " << studInfo[i].studentID << endl;
                            cout << "Full Name       :: " << studInfo[i].fullName.lastName << ", " << studInfo[i].fullName.firstName << ' ' << studInfo[i].fullName.middleName << endl;
                            cout << "Sex             :: " << studInfo[i].sex << endl;
                            cout << "Date of Birth   :: " << studInfo[i].birthDate.month << '/' << studInfo[i].birthDate.day << '/' << studInfo[i].birthDate.year << endl;
                            cout << "Phone Number    :: " << studInfo[i].phoneNumber << endl;
                            cout << "Email           :: " << studInfo[i].email << endl;
                            cout << "Address         :: " << studInfo[i].address << endl;
                            cout << "Course Enrolled :: " << studInfo[i].courseEnrolled << endl;
                            found3 = true;
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
                        if (!found3)
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
    int sel;
    char selC;
    while ("true")
    {
        cout << "Student Management System\n";
        cout << "-----------Menu-----------\n";
        cout << " 1. Student Registration and Enrollment\n";
        cout << " 2. Manage Student Records\n";
        cout << " 3. Generate Reports\n";
        cout << "Selection: ";
        cin >> sel;
        process.getMainUserSelect(sel);
    }

return 0;
}