#include <iostream>
#include <vector>
#include <sqlite3.h>

using namespace std;

int main() {
    vector<string> nem;
    nem.push_back("TESTING");
    sqlite3* db;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "ERROR OPENING DATABASE: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return rc;
    }

    char* sql = "CREATE TABLE IF NOT EXISTS testTable (id INTEGER PRIMARY KEY, testname TEXT);";
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Error creating table: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return rc;
    }

    // Insert data into the database
    string data = nem[0];
    char* errMsg;
    string sqlInsert = "INSERT INTO testTable (testname) VALUES ('" + data + "');";
    rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
    return 0;
}
