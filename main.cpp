#include <iostream>
#include <vector>
using namespace std;

class dBaseAccess{
    private:
    
    public:
    
};

class processing: public dBaseAccess{
    private:

        void mgmStdRecords(){
            char selC;
            do
            {
            cout << "A. " << endl;
            cout << "B. " << endl;
            cout << "C. " << endl;
            cin >> selC;
            if (selC == 'a' || 'A')
            {
                /* code */
            }
            else if (selC == 'b' || 'B')
            {
                /* code */
            }
            else if (selC == 'c' || 'C')
            {
                /* code */
            }
            else
            {
                cout << "Invalid Selection!!!";
            }
            } while ("true");
            
        }

        void stdRegNenroll(){
            char selC;
            do
            {
            cout << "A. " << endl;
            cout << "B. " << endl;
            cout << "C. " << endl;
            cin >> selC;
            if (selC == 'a' || 'A')
            {
                /* code */
            }
            else if (selC == 'b' || 'B')
            {
                /* code */
            }
            else if (selC == 'c' || 'C')
            {
                /* code */
            }
            else
            {
                cout << "Invalid Selection!!!";
            }
            } while ("true");
        }

        void genReports(){
            char selC;
            do
            {
            cout << "A. " << endl;
            cout << "B. " << endl;
            cout << "C. " << endl;
            cin >> selC;
            if (selC == 'a' || 'A')
            {
                /* code */
            }
            else if (selC == 'b' || 'B')
            {
                /* code */
            }
            else if (selC == 'c' || 'C')
            {
                /* code */
            }
            else
            {
                cout << "Invalid Selection!!!";
            }            
            } while ("true");
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
    do
    {
    cout << "Student Management System\n";
    cout << "-----------Menu-----------\n";
    cout << " 1. Manage Student Records\n";
    cout << " 2. Student Registration and Enrollment\n";
    cout << " 3. Generate Reports\n";
    cout << "Selection: ";
    cin >> sel;
    process.getMainUserSelect(sel);
    } while ("true");
    
return 0;
}