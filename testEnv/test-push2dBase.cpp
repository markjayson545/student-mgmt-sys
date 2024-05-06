#include <iostream>
#include <vector>
#include <sqlite3.h>
using namespace std;

struct studInfo
{
    string name;
    int age;
};
vector <studInfo> studenInformation;

int main(){

    for (int i = 0; i < 10; i++)
    {
    studInfo studIInfo;
    studIInfo.name = "TEST NAME";
    studIInfo.age = 100;
    studenInformation.push_back(studIInfo);
    }
    

    // create and open Dbase
    sqlite3* db;
    int rc;
    rc = sqlite3_open("studInfo.db", &db);
    if (rc != SQLITE_OK)
    {
        cerr << "Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }
    char* sql = "CREATE TABLE IF NOT EXISTS studnetInformation (name TEXT, age INTEGER);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        cerr << "Error Creating table: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }


    for (int i = 0; i < studenInformation.size(); i++)
    {
        string pushName = studenInformation[i].name;
        int pushAge = studenInformation[i].age;
        char* errMsg;
        string sqlInsert = "INSERT INTO studnetInformation (name, age)"
                            "VALUES ('" + pushName + "',"
                            "'" + to_string(pushAge) + "');";
        rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &errMsg);
        if (rc != SQLITE_OK)
        {
            cerr << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
    }
    
        

        sqlite3_close(db);
    return 0;
}