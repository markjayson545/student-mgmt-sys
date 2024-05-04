#include <iostream>
#include <vector>
#include <sqlite3.h>

using namespace std;

// Function to insert data into the database
int insertid(sqlite3* db, const string& data) {
    char* errMsg;
    string sql = "INSERT INTO testTable (testname) VALUES ('" + data + "');";
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

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

    rc = insertid(db, nem[0]);
    if (rc != SQLITE_OK) {
        cerr << "Error insertion: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_close(db);
    return 0;
}
