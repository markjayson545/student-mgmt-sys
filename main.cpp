#include <iostream>
#include <vector>
using namespace std;

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
                cout << "1. Register New Student" << endl;
                cout << "2. Enroll Student in Course" << endl;
                cout << "3. Drop Course" << endl;
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