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
    string address;
    int phoneNumber;
    char sex;
    string email;
};

vector <studentInfo> studInfo;

class dBaseAccess{
    private:
    
    public:
    
};

class processing{
    private:

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
                    cout << "Enter Last Name: ";
                    getline(cin, student.fullName.lastName);
                    cout << "Enter First Name:";
                    getline(cin, student.fullName.firstName);
                    cout << "Enter Middle Name:";
                    getline(cin, student.fullName.middleName);
                    do
                    {
                    cout << "Enter Birthdate:" << endl << "Month (1-12): ";
                    cin >> student.birthDate.month;
                    if (student.birthDate.month >= 12 || student.birthDate.month <= 0)
                    {
                        cout << "Invalid input!";
                    }                                       
                    } while (student.birthDate.month >= 12 || student.birthDate.month <= 0);
                    

                    cout << "Day: ";
                    cin >> student.birthDate.day;
                    cout << "Year: ";
                    cin >> student.birthDate.year;
                    studInfo.push_back(student);

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
                mgmStdRecords();
                break;
            case 2:
                stdRegNenroll();
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
        cout << " 1. Manage Student Records\n";
        cout << " 2. Student Registration and Enrollment\n";
        cout << " 3. Generate Reports\n";
        cout << "Selection: ";
        cin >> sel;
        process.getMainUserSelect(sel);
    }

return 0;
}