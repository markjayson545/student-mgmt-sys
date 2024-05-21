#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

const string MANAGER_PASSWORD = "kasyanbsit1b";
const float EXCHANGE_RATE = 48.50;
const float PHILHEALTH_RATE = 1000;
const float PAY_RATE_PER_HOUR = 100.0;
const float PAY_RATE_PER_MINUTE = PAY_RATE_PER_HOUR / 60.0;
const float OVERTIME_RATE = PAY_RATE_PER_HOUR * 1.05;
const float DEDUCTION_RATE = PAY_RATE_PER_HOUR * 0.95;

struct Employee {
    int empId;
    string name;
    string phoneNumber;
    string maritalStatus;
    string department;
    string position;
    string employmentType;
    string manager;
    string taxId;
    string bankId;
    string emergencyContact;
    int basic, ma;
    int pf, insurance;
    float gross, net;
    int taxes, philhealth, sss;
    float overtimeHours, overtimeMinutes;
    float deductionHours, deductionMinutes;
};

struct AttendanceRecord {
    int empId;
    vector<pair<string, string>> checkInOutTimes;
};

vector<Employee> employees;
vector<AttendanceRecord> attendanceRecords;

void saveEmployeesToFile() {
    ofstream outFile("employees.txt");
    for (const auto& e : employees) {
        outFile << e.empId << "\n" << e.name << "\n" << e.phoneNumber << "\n" << e.maritalStatus << "\n"
                << e.department << "\n" << e.position << "\n" << e.employmentType << "\n" << e.manager << "\n"
                << e.taxId << "\n" << e.bankId << "\n" << e.emergencyContact << "\n" << e.basic << "\n"
                << e.ma << "\n" << e.pf << "\n" << e.insurance << "\n" << e.overtimeHours << "\n" << e.overtimeMinutes << "\n"
                << e.deductionHours << "\n" << e.deductionMinutes << "\n";
    }
    outFile.close();
}

void loadEmployeesFromFile() {
    ifstream inFile("employees.txt");
    Employee e;
    while (inFile >> e.empId) {
        inFile.ignore();
        getline(inFile, e.name);
        getline(inFile, e.phoneNumber);
        getline(inFile, e.maritalStatus);
        getline(inFile, e.department);
        getline(inFile, e.position);
        getline(inFile, e.employmentType);
        getline(inFile, e.manager);
        getline(inFile, e.taxId);
        getline(inFile, e.bankId);
        getline(inFile, e.emergencyContact);
        inFile >> e.basic >> e.ma >> e.pf >> e.insurance >> e.overtimeHours >> e.overtimeMinutes >> e.deductionHours >> e.deductionMinutes;
        employees.push_back(e);
    }
    inFile.close();
}

void saveAttendanceToFile() {
    ofstream outFile("attendance.txt");
    for (const auto& record : attendanceRecords) {
        outFile << record.empId << "\n";
        for (const auto& checkInOut : record.checkInOutTimes) {
            outFile << checkInOut.first << " " << checkInOut.second << "\n";
        }
        outFile << "-1\n";
    }
    outFile.close();
}

void loadAttendanceFromFile() {
    ifstream inFile("attendance.txt");
    AttendanceRecord record;
    while (inFile >> record.empId) {
        string checkIn, checkOut;
        while (inFile >> checkIn && checkIn != "-1") {
            inFile >> checkOut;
            record.checkInOutTimes.push_back({checkIn, checkOut});
        }
        attendanceRecords.push_back(record);
        record.checkInOutTimes.clear();
    }
    inFile.close();
}

void inputEmployeeDetails(Employee &e) {
    cout << "Enter Employee ID: ";
    cin >> e.empId;
    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, e.name);

    cout << "Enter Employee Phone Number: ";
    getline(cin, e.phoneNumber);

    cout << "Enter Employee Marital Status: ";
    getline(cin, e.maritalStatus);

    cout << "Enter Employee Department: ";
    getline(cin, e.department);

    cout << "Enter Employee Position: ";
    getline(cin, e.position);

    cout << "Enter Employee Employment Type: ";
    getline(cin, e.employmentType);

    cout << "Enter Employee Manager: ";
    getline(cin, e.manager);

    cout << "Enter Employee Tax ID: ";
    getline(cin, e.taxId);

    cout << "Enter Employee Bank ID: ";
    getline(cin, e.bankId);

    cout << "Enter Employee Emergency Contact: ";
    getline(cin, e.emergencyContact);

    cout << "Enter Employee Basic Salary (in PHP): ";
    cin >> e.basic;

    cout << "Enter Employee MA (Medical Allowance) (in PHP): ";
    cin >> e.ma;

    cout << "Enter Employee PF (Provident Fund) (in PHP): ";
    cin >> e.pf;

    cout << "Enter Employee Insurance (in PHP): ";
    cin >> e.insurance;

    string overtime, deduction;
    cout << "Enter Employee Overtime (format: Xh Ymins): ";
    cin.ignore();
    getline(cin, overtime);
    cout << "Enter Employee Deduction (format: Xh Ymins): ";
    getline(cin, deduction);

    // Parse the overtime and deduction strings
    sscanf(overtime.c_str(), "%fh %fmins", &e.overtimeHours, &e.overtimeMinutes);
    sscanf(deduction.c_str(), "%fh %fmins", &e.deductionHours, &e.deductionMinutes);
}

void updateEmployeeRecord(Employee &e) {
    cout << "Update Employee Details for ID " << e.empId << ":\n";
    inputEmployeeDetails(e);
}

void calculateSalary(Employee &e) {
    float overtimePay = (e.overtimeHours * OVERTIME_RATE) + (e.overtimeMinutes * OVERTIME_RATE / 60);
    float deductionPay = (e.deductionHours * DEDUCTION_RATE) + (e.deductionMinutes * DEDUCTION_RATE / 60);

    e.gross = e.basic + e.ma + overtimePay - deductionPay;
    e.taxes = 0.12 * e.gross;
    e.philhealth = PHILHEALTH_RATE;
    e.sss = 1500;
    e.net = e.gross - (e.taxes + e.philhealth + e.sss);
}

void printSalary(const Employee& e) {
    cout << fixed << setprecision(2);
    cout << "Salary Slip for Employee ID " << e.empId << ":\n";
    cout << "Gross Salary: PHP " << e.gross << endl;
    cout << "Overtime Payment: PHP " << (e.overtimeHours * OVERTIME_RATE) + (e.overtimeMinutes * OVERTIME_RATE / 60) << endl;
    cout << "Deduction for Lateness: PHP " << (e.deductionHours * DEDUCTION_RATE) + (e.deductionMinutes * DEDUCTION_RATE / 60) << endl;
    cout << "Deductions:\n";
    cout << "  Taxes: PHP " << e.taxes << endl;
    cout << "  PhilHealth: PHP " << e.philhealth << endl;
    cout << "  SSS: PHP " << e.sss << endl;

    float totalDeductions = e.taxes + e.philhealth + e.sss;
    cout << "Total Deductions: PHP " << totalDeductions << endl;

    cout << "Net Salary: PHP " << e.net << endl;
}

void display(const Employee& e) {
    cout << e.empId << "\t" << e.name << "\t" << e.basic << "\t" << e.ma << "\t"
         << e.pf << "\t" << e.insurance << "\t" << e.taxes << "\t"
         << e.philhealth << "\t" << e.sss << endl;
}

void recordAttendance(Employee &e, vector<AttendanceRecord> &attendanceRecords) {
    AttendanceRecord record;
    record.empId = e.empId;
    cout << "Enter check-in time (HH:MM AM/PM): ";
    string checkIn;
    cin.ignore();
    getline(cin, checkIn);
    cout << "Enter check-out time (HH:MM AM/PM): ";
    string checkOut;
    getline(cin, checkOut);
    record.checkInOutTimes.push_back({checkIn, checkOut});
    attendanceRecords.push_back(record);
}

void displayAttendance(const vector<AttendanceRecord> &attendanceRecords, const vector<Employee> &employees) {
    cout << "Select an option:\n";
    cout << "1) Display all attendance records\n";
    cout << "2) Display attendance records for a specific employee\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Employee ID\tCheck-In\tCheck-Out\n";
            for (const auto& record : attendanceRecords) {
                cout << record.empId << "\t";
                for (const auto& checkInOut : record.checkInOutTimes) {
                    cout << checkInOut.first << "\t" << checkInOut.second << endl;
                }
            }
            break;
        case 2:
            cout << "Enter the Employee ID to display attendance records: ";
            int empID;
            cin >> empID;
            {
                auto it = find_if(attendanceRecords.begin(), attendanceRecords.end(), [&](const AttendanceRecord& record) { return record.empId == empID; });
                if (it != attendanceRecords.end()) {
                    cout << "Check-In\tCheck-Out\n";
                    for (const auto& checkInOut : it->checkInOutTimes) {
                        cout << checkInOut.first << "\t" << checkInOut.second << endl;
                    }
                } else {
                    cout << "No attendance records found for employee " << empID << endl;
                }
            }
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

void deleteEmployeeRecord(int empID) {
    auto it = remove_if(employees.begin(), employees.end(), [&](const Employee& e) { return e.empId == empID; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "Employee record deleted successfully.\n";
        saveEmployeesToFile();
    } else {
        cout << "Employee not found.\n";
    }
}

void deleteAttendanceRecord(int empID) {
    auto it = remove_if(attendanceRecords.begin(), attendanceRecords.end(), [&](const AttendanceRecord& record) { return record.empId == empID; });
    if (it != attendanceRecords.end()) {
        attendanceRecords.erase(it, attendanceRecords.end());
        cout << "Attendance record deleted successfully.\n";
        saveAttendanceToFile();
    } else {
        cout << "Attendance record not found.\n";
    }
}

int main() {
    int choice;
    loadEmployeesFromFile();
    loadAttendanceFromFile();

    do {
        cout << "Are you an employee or a manager?\n";
        cout << "1) Employee\n";
        cout << "2) Manager\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                Employee newEmployee;
                inputEmployeeDetails(newEmployee);
                employees.push_back(newEmployee);
                cout << "Employee details entered successfully!\n";
                saveEmployeesToFile();
                break;
            }
            case 2: {
                cout << "Welcome, Manager!\n";
                string managerPassword;
                cout << "Enter Manager Password: ";
                cin >> managerPassword;
                if (managerPassword != MANAGER_PASSWORD) {
                    cout << "Incorrect password. Access denied!\n";
                    return 0;
                }

                while (true) {
                    cout << "\n   EMPLOYEE PAYROLL SYSTEM \n";
                    cout << "\n\n*****CHOOSE YOUR OPTION*****\n";
                    cout << "1) SHOW ALL RECORDS\n";
                    cout << "2) ADD NEW EMPLOYEE RECORD\n";
                    cout << "3) PRINT THE SALARY SLIP OF GIVEN EMPLOYEE\n";
                    cout << "4) UPDATE AN EMPLOYEE RECORD\n";
                    cout << "5) RECORD ATTENDANCE\n";
                    cout << "6) DISPLAY ATTENDANCE RECORDS\n";
                    cout << "7) DELETE AN EMPLOYEE RECORD\n";
                    cout << "😎 DELETE AN ATTENDANCE RECORD\n";
                    cout << "9) EXIT\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    int empID;
                    switch (choice) {
                        case 1:
                            cout << "EmpID\tName\tBasic\tMA\tPF\tInsurance\tTaxes\tPhilHealth\tSSS\n";
                            for (const auto& e : employees) {
                                display(e);
                            }
                            break;
                        case 2:
                            employees.resize(employees.size() + 1);
                            inputEmployeeDetails(employees.back());
                            saveEmployeesToFile();
                            break;
                        case 3:
                            cout << "Enter Employee ID to generate salary slip: ";
                            cin >> empID;
                            {
                                auto it = find_if(employees.begin(), employees.end(), [&](const Employee& e) { return e.empId == empID; });
                                if (it != employees.end()) {
                                    calculateSalary(*it);
                                    printSalary(*it);
                                } else {
                                    cout << "Employee not found!\n";
                                }
                            }
                            break;
                        case 4:
                            cout << "Enter Employee ID to update: ";
                            cin >> empID;
                            {
                                auto it = find_if(employees.begin(), employees.end(), [&](const Employee& e) { return e.empId == empID; });
                                if (it != employees.end()) {
                                    updateEmployeeRecord(*it);
                                    saveEmployeesToFile();
                                } else {
                                    cout << "Employee not found!\n";
                                }
                            }
                            break;
                        case 5:
                            cout << "Enter Employee ID to record attendance: ";
                            cin >> empID;
                            {
                                auto it = find_if(employees.begin(), employees.end(), [&](const Employee& e) { return e.empId == empID; });
                                if (it != employees.end()) {
                                    recordAttendance(*it, attendanceRecords);
                                    cout << "Attendance recorded for employee " << empID << endl;
                                    saveAttendanceToFile();
                                } else {
                                    cout << "Employee not found!\n";
                                }
                            }
                            break;
                        case 6:
                            displayAttendance(attendanceRecords, employees);
                            break;
                        case 7:
                            cout << "Enter Employee ID to delete: ";
                            cin >> empID;
                            deleteEmployeeRecord(empID);
                            break;
                        case 8:
                            cout << "Enter Employee ID to delete attendance record: ";
                            cin >> empID;
                            deleteAttendanceRecord(empID);
                            break;
                        case 9:
                            cout << "Goodbye!\n";
                            return 0;
                        default:
                            cout << "Invalid choice! Try again.\n";
                    }
                }
                break;
            }
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (true);

    return 0;
}