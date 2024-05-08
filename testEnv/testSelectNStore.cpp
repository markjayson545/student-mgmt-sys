#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>

using namespace std;

int main() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "ERROR OPENING DATABASE: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    // Sample SELECT statement (assuming a table named 'testTable')
    const char* sql = "SELECT testname FROM testTable";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing SELECT statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    vector<string> data;

    // Loop through results and store data directly
    while (rc = sqlite3_step(stmt) == SQLITE_ROW) {
        const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (value) {
            data.push_back(string(value));
        } else {
            data.push_back("NULL");  // Handle null values explicitly
        }
    }

    // Handle potential errors
    if (rc != SQLITE_DONE) {
        cerr << "Error retrieving data: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (!data.empty()) {
        cout << "Retrieved data:" << endl;
        for (const string& value : data) {
            cout << value << endl;
        }
    } else {
        cout << "No data found." << endl;
    }

    return 0;
}
