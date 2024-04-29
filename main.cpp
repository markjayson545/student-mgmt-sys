#include <iostream>
using namespace std;

class dBaseAccess{
    private:

    public:
    
};

class processing: public dBaseAccess{
    private:

    void mgmStdRecords(){
        
    }
    void stdRegNenroll(){

    }
    void genReports(){

    }

    public:

};

class getInputs: public processing{
    private:
        void getSel(int sel){
            switch (sel)
            {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            default:
            cout << "Invalid Selection";
                break;
            }
        }
    public:
        void runSel(int sel){
            getSel(sel);
        }
};



int main(){
    getInputs inputs;
    int sel;
    char selC;

    cout << "Student Management System\n";
    cout << "-----------Menu-----------\n";
    cout << " 1. Manage Student Records\n";
    cout << " 2. Student Registration and Enrollment\n";
    cout << " 3. Generate Reports\n";
    cout << "Selection: ";
    cin >> sel;
    inputs.runSel(sel);
return 0;
}